#include <stdio.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>

void handler_sigtime(int signo)
{
    switch(signo)
    {
    case SIGALRM:
        printf("recv SIGALRM\n");
        break;
    case SIGPROF:
        printf("recv SIGPROF\n");
        break;
    default:
        break;
    }
}

int main()
{
    struct itimerval value;

    signal(SIGALRM,handler_sigtime);
    signal(SIGPROF,handler_sigtime);

    value.it_value.tv_sec = 1;      //第一次1秒触发信号
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 5;   //第二次5秒触发信号
    value.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL,&value,NULL);
    setitimer(ITIMER_PROF,&value,NULL);

    while(1);

    return 0;
}

