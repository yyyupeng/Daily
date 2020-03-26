#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

#define gettid() syscall(__NR_gettid)

pthread_t ntid;

void *printids(void *s)
{
    pid_t pid;      //进程号
    pid_t ktid;     //内核级线程号
    pthread_t utid; //用户级线程号

    pid = getpid(); 
    ktid = gettid();
    utid = pthread_self();

    printf("%s pid %u ktid %u utid %u (0x%x)\n", s, (unsigned int)pid, (unsigned int)ktid, (unsigned int)utid, (unsigned int)utid);

    pause();
}

int main()
{
    pthread_create(&ntid, NULL,printids, " new thread:");
    printids("main thread:");
    sleep(10);
    return 0;
}
