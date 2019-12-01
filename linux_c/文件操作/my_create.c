#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main(int argc, char *argv[])
{
    int fd;
    if((fd = open("test2",O_CREAT|O_EXCL,S_IRUSR|S_IWUSR)) == -1)
    {
        perror("open");
        printf("with errno:%d\n",errno);
        exit(1);
    }
    else
        printf("create file success\n");
    close(fd);
    return 0;
}
