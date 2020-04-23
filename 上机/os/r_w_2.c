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
    int init2 = sem_init(&sread, 0, 1);
    if( (init1 != 0) && (init2 != 0))
    {
        printf("sem init failed \n");
        exit(1);
    }
}

void *reader(void *arg)
{
    P(sdata);
    for(int i = 0; i < M ; ++i)
        P(sread);

    for(int i = 0; i < M ; ++i)
        V(sread);
    V(sdata);

    return NULL;
}

void *writer(void *arg)
{
    P(sdata);
    P(sread);
    V(sdata);

    V(sread);

    return NULL;
}

int main()
{
    pthread_t id1[N];
    pthread_t id2[N];

    sem_mutex_init();
    
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
