#include <stdio.h>
#include<signal.h>
#include<unistd.h>

int t = 0;

void handler_sigint(int signo)
{
    printf("recv SIGINT\n");
    sleep(5);
    t += 1;
    printf("the value of t is: %d\n",t);
    printf("in handler_sigint,after sleep\n");
}

int main()
{
    struct sigaction act;

    act.sa_handler = handler_sigint;
    //act.sa_flags = SA_NOMASK;

    sigaction(SIGINT,&act,NULL);

    while(1);

    return 0;
}

