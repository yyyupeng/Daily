#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>

#define PORT 9527
#define MAX_EVEVT 1000
static int pipefd[2];

/* 将文件描述符设置为非阻塞 */
int setnonblockong(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

/* 注册事件并设置为ET模式 */
void addfd(int epfd, int fd)
{
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    setnonblockong(fd);
}

/* 信号处理函数 */
void sig_handler(int sig)
{
    //保留原来的errno，在函数最后恢复，以保证函数的可重入型
    int save_errno = errno;
    int msg = sig;
    send(pipefd[1], (char *)&msg, 1, 0);
    errno = save_errno;
}

/* 设置信号的处理函数 */
void addsig(int sig)
{
    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(struct sockaddr_in);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);
    int ret = bind(sockfd, (struct sockaddr *)&servaddr, len);
    assert(ret != -1);
    ret = listen(sockfd, 5);
    assert(ret != -1);

    epoll_event evevts[MAX_EVEVT];
    int epfd = epoll_create(5);
    assert(epfd != -1);
    addfd(epfd, sockfd);

    //使用socketpair创建管道，注册pipefd[0]上的可读事件
    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
    assert(ret != -1);
    setnonblockong(pipefd[1]);
    addfd(epfd, pipefd[0]);

    //设置信号处理函数
    addsig(SIGHUP);
    addsig(SIGCHLD);
    addsig(SIGTERM);
    addsig(SIGINT);
    bool stop_server = false;

    while(!stop_server)
    {
        int num = epoll_wait(epfd, evevts, MAX_EVEVT, -1);
        if((num < 0) && (errno != EINTR))
        {
            printf("rpoll failure!\n");
            break;
        }

        for(int i = 0; i < num; ++i)
        {
            //就绪的文件描述符是sockfd
            if(sockfd == evevts[i].data.fd)
            {
                connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
                addfd(epfd, connfd);
            }
            //就绪的文件描述符是pipefd[0]
            else if((pipefd[0] == evevts[i].data.fd) && (evevts[i].events == EPOLLIN))
            {
                int sig;
                char signals[1000];
                ret = recv(pipefd[0], signals, sizeof(signals), 0);
                if((ret == -1) || (ret == 0))
                    continue;
                else
                {
                    //每个信号占一个字节
                    for(int j = 0; j < ret; ++j)
                    {
                        switch(signals[j])
                        {
                        case SIGCHLD:
                        case SIGHUP:
                            continue;
                        case SIGTERM:
                        case SIGINT:
                            stop_server = true;
                        }
                    }
                }
            }
        }
    }
    printf("close fds\n");
    close(sockfd);
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}

