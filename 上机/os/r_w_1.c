#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10            
#define P(x)    sem_wait(&x)
#define V(x)    sem_post(&x)

int readcount; 

sem_t sdata;
sem_t srcount;

void sem_mutex_init()
{
    int init1 = sem_init(&sdata, 0, 1);
    int init2 = sem_init(&srcount, 0, 1);
    if( (init1 != 0) && (init2 != 0))
    {
        printf("sem init failed \n");
        exit(1);
    }
}

void *reader(void *arg)
{
    P(srcount);
    ++readcount;
    if(readcount == 1)
        P(sdata);
    V(srcount);
    printf("I'm reader.\n");
    P(srcount);
    --readcount;
    if(readcount == 0)
        V(sdata);    
    V(srcount);

    return NULL;
}

void *writer(void *arg)
{
    P(sdata);
    printf("I'm writer.\n");
    V(sdata);

    return NULL;
}

int main()
{
    sem_mutex_init();

    pthread_t id[N];
    int i = 0;
    char ch;
    while(1)
    {
        scanf("%c", &ch);
        if(ch == 'q')
            break;
        if(ch == 'r')
            pthread_create(&id[i++], NULL, reader, NULL);
        else if(ch == 'w')
            pthread_create(&id[i++], NULL, writer, NULL);
    } 
    
    sem_destroy(&sdata);
    sem_destroy(&srcount);
    for(int j = 0; j < i; ++j)
        pthread_join(id[j],NULL);

    return 0;
}
