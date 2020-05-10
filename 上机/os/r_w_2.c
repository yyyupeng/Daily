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
    while(1)
    {
        sleep(2);
        P(sdata);
        for(int i = 0; i < M ; ++i)
            P(sread);
        printf("I'm writer.\n");
        for(int i = 0; i < M ; ++i)
            V(sread);
        V(sdata);
    }
    return NULL;
}

void *reader(void *arg)
{
    while(1)
    {
        sleep(1);
        P(sdata);
        P(sread);
        V(sdata);
        printf("I'm reader.\n");
        V(sread);
    }
    return NULL;
}

int main()
{
    sem_mutex_init();
    
    pthread_t id1[N], id2[N];
    for(int i = 0; i < N; ++i)
        pthread_create(&id1[i], NULL, reader, NULL);
    for(int i = 0; i < N; ++i)
        pthread_create(&id2[i], NULL, writer, NULL);

    sem_destroy(&sdata);
    sem_destroy(&sread);
    
    for(int i = 0; i < N; ++i)
        pthread_join(id1[i],NULL);
    for(int i = 0; i < N; ++i)
        pthread_join(id2[i],NULL);

    return 0;
}
