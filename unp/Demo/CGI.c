#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* CGI服务器：将标准输出重定向到一个网络连接 */

int main()
{
    /* ... */
    close(STDOUT_FILENO);   //关闭标准输出文件描述符（1）
    dup(sock_fd);           //"复制"fd，返回系统中可用的最小文件描述符（1）
    printf("hello");        //"hello"会直接发送到与客户连接的sock上，也就是被客户端获得（而不是输出到服务器的终端上）
    /* ... */
    return 0;
}

