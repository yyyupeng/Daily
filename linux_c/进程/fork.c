#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    printf("***计科1807——李宇鹏***\n\n");
    pid_t pid;
    printf("Before fork...\n");
    pid = fork();
    switch(pid)
    {
    case 0:
        printf("A background process, PID: %d, ParentID: %d\n",getpid(),getppid());
        exit(0);
    case -1:
        perror("Process creation failed\n");
        exit(-1);
    default:
        printf("I am parent process, my pid is %d, ChildID: %d\n",getpid(), pid);
        exit(0);
    }
    printf("After fork, program exiting...\n");
    return 0;
}

