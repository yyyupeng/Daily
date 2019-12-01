#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define MAXLINE 4096

void my_err(const char *err_string, int line)
{
    fprintf(stderr, "line: %d", line);
    perror(err_string);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
         my_err("socket", __LINE__);    
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /*
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        printf("inet_pton error for %s\n", argv[1]);
        exit(1);
    }
    */
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_in)) < 0)
        my_err("connect", __LINE__);

    while((n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = '\0';
        if(fputs(recvline, stdout) == EOF)
            my_err("fputs", __LINE__);
    }
    if(n < 0)
        my_err("read", __LINE__);

    return 0;
}

