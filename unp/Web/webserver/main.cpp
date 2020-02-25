#include "code/task.h"
#include "code/threadpool.h"

void my_err(const char *err_string, int line)
{
    fprintf(stderr, "line: %d", line);
    perror(err_string);
    exit(1);
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

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
         my_err("socket", __LINE__);
    if(bind(sockfd, (struct sockaddr *)&servaddr, len) < 0)
        my_err("bind",__LINE__);
    if(listen(sockfd, 10) < 0)
        my_err("listen",__LINE__);
    cout << "socked successful..." << endl;

    threadpool<task> pool;
    cout << "threadpool successful..." << endl;

    while(1)
    {
        if((connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len)) < 0)
            my_err("accept", __LINE__);
        cout << "\n" << "connect " << connfd << endl;
        
        task *ta = new task(connfd);
        pool.appjob(ta);
    }

    return 0;
}
