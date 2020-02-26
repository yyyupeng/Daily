#include "../webserver/code/include.h"
#include <sys/sendfile.h>

int main()
{
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
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
    cout << "socket successful" << endl;

    while(1)
    {
        int connfd = accept(sockfd, (struct sockaddr *)&client, &len);
        if(connfd < 0)
            printf("errno is %d\n", errno);
        else
        {
            char ch[1024];
            recv(connfd, ch, 1024, 0);
            cout << ch << endl;
            cout << "successful!" << endl;
            //HTTP响应
            char buf[512] = "HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";
            int s = send(connfd, buf, strlen(buf), 0);//发送响应
            cout << s << endl;
            int fd = open("test.html",O_RDONLY);//消息体
            sendfile(connfd, fd, NULL, 3000);//零拷贝发送消息体
            close(fd);
            close(connfd);
        }
    }
    return 0;
}

