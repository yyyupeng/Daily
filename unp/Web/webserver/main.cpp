#include "code/task.h"
#include "code/threadpool.h"
#define MAX_EVENT 10000

/* 错误处理函数 */
void my_err(const char *err_string, int line)
{
    fprintf(stderr, "line: %d", line);
    perror(err_string);
    exit(1);
}

/* 将文件描述符设置为非阻塞 */
int setnonblockong(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

/* 注册事件并设置为ET模式 */
void addfd(int epfd, int fd, bool one_shot)
{
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLET | EPOLLRDHUP; 
    if(one_shot)
    {
        ev.events |= EPOLLONESHOT;
    }
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    setnonblockong(fd);
}

int flag_happen;
void handler_sigint(int signo)
{
    flag_happen = 1;
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(struct sockaddr_in);

    //信号处理函数
    if(signal(SIGINT, handler_sigint) == SIG_ERR)
        my_err("signal", __LINE__);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
         my_err("socket", __LINE__);
    if(bind(sockfd, (struct sockaddr *)&servaddr, len) < 0)
        my_err("bind",__LINE__);
    if(listen(sockfd, 10) < 0)
        my_err("listen",__LINE__);
    cout << "socked successful..." << endl;

    epoll_event events[MAX_EVENT];
    int epfd = epoll_create(5);
    assert(epfd != -1);
    addfd(epfd, sockfd, false);
    cout << "epoll successful..." << endl;

    threadpool<task> pool;
    cout << "threadpool successful..." << endl;
    
    task *ta = NULL;
    while(1)
    {
        int ret = epoll_wait(epfd, events, MAX_EVENT, -1);
        for(int i = 0; i < ret; ++i)
        {
            if(events[i].data.fd == sockfd)
            {
                if((connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len)) < 0)
                    my_err("accept", __LINE__);
                cout << "\n" << "connect:" << connfd << endl;
                addfd(epfd, connfd, true);
            }
            else if(events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
            {
                epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, 0);
                close(events[i].data.fd);
            }
            else if(events[i].events & EPOLLIN)
            {
                ta = new task(connfd);
                pool.appjob(ta);
            }
        }
        if(flag_happen == 1)
        {
            cout << "\n" << "Rookie server is shutting down..." << endl;
            break;
        }
    }
    
    close(sockfd);
    close(epfd);
    delete ta;
    return 0;
}
