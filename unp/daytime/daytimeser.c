#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define MAXLINE 4096

void my_err(const char *err_string, int line)
{
    fprintf(stderr, "line: %d", line);
    perror(err_string);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(struct sockaddr_in);
    char buf[MAXLINE];
    time_t ticks;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
         my_err("socket", __LINE__);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr *)&servaddr, len) < 0)
        my_err("bind",__LINE__);
    
    if(listen(sockfd, 10) < 0)
        my_err("listen",__LINE__);

    while(1)
    {
        if((connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len)) < 0)
            my_err("accept", __LINE__);
        ticks = time(NULL);
        snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
        if(write(connfd, buf, strlen(buf)) != strlen(buf))
            my_err("write", __LINE__);

        close(connfd);
    }
    return 0;
}
