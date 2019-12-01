#include <stdio.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/types.h>

int main()
{
    long ID1, ID2; 
    //系统调用
    ID1 = getpid();
    printf("getpid() = %ld\n", ID1);

    //调用内核函数
    ID2 = syscall(SYS_getpid);
    printf("syacall(SYS_getpid) = %ld\n", ID2);

    return 0;
}

