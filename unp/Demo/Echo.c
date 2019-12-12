#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* 回射服务器：将客户端发送的数据原样返回给客户端 */

int main()
{
    /* ... */
    /* splice()——在文件描述符间移动数据，零拷贝操作 */
    int pipefd[2];
    int ret = pipe(pipefd);     //创建管道
    //将fd上流入的客户数据定向到管道
    ret = splice(sock_fd, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE); 
    //将管道的输出定向到fd客户连接文件描述符
    ret = splice(pipefd[0], NULL, sock_fd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
    /* ... */
    return 0;
}

