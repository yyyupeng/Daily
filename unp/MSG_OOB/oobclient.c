#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

#define BUF_SIZE 1024
#define PORT 8888

int main()
{
    struct sockaddr_in server;
    bzero(&server, sizeof(server));

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
        printf("连接失败！\n");
    else
    {
        const char *a = "abc";
        const char *b = "123";
        send(sockfd, b, strlen(b), 0);
        send(sockfd, a, strlen(a), MSG_OOB);
        send(sockfd, b, strlen(b), 0);
    }
    close(sockfd);
    return 0;
}

