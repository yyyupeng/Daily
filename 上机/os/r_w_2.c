#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10            
#define M 20
#define P(x)    sem_wait(&x)
#define V(x)    sem_post(&x)

sem_t sdata;
sem_t sread;

void sem_mutex_init()
{
    int init1 = sem_init(&sdata, 0, 1);
    int init2 = sem_init(&sread, 0, M);
    if( (init1 != 0) && (init2 != 0))
    {
        printf("sem init failed \n");
        exit(1);
    }
}

void *writer(void *arg)
{
    P(sdata);
    for(int i = 0; i < M ; ++i)
        P(sread);
    printf("I'm writer.\n");
    for(int i = 0; i < M ; ++i)
        V(sread);
    V(sdata);
    return NULL;
}

void *reader(void *arg)
{
    P(sdata);
    P(sread);
    V(sdata);
    printf("I'm reader.\n");
    V(sread);
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
    sem_destroy(&sread);
    for(int j = 0; j < i; ++j)
        pthread_join(id[j],NULL);

    return 0;
}
