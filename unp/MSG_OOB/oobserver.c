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

    int ret = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    assert(ret != -1);

    ret = listen(sockfd, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    int connfd = accept(sockfd, (struct sockaddr *)&client, &len);
    if(connfd < 0)
        printf("errno is %d\n", errno);
    else
    {
        char buf[BUF_SIZE];
        
        bzero(buf, sizeof(buf));
        ret = recv(connfd, buf, BUF_SIZE - 1, 0);
        printf("got %d bytes is '%s'\n", ret, buf);
        
        //带外数据
        bzero(buf, sizeof(buf));
        ret = recv(connfd, buf, BUF_SIZE - 1, MSG_OOB);
        printf("got %d bytes is '%s'\n", ret, buf);

        bzero(buf, sizeof(buf));
        ret = recv(connfd, buf, BUF_SIZE - 1, 0);
        printf("got %d bytes is '%s'\n", ret, buf);
 
        close(connfd);
    }
    close(sockfd);
    return 0;
}

