#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 3             //*缓冲数目
#define N 1            //p_s数目
#define P(x)     sem_wait(&x)
#define V(x)     sem_post(&x)

int in = 0;             //生产者放置产品的位置
int out = 0;             //消费者取产品的位置

int buff[M];

sem_t empty_sem;         
sem_t full_sem;  
sem_t buf;

void sem_mutex_init()
{
    int init1 = sem_init(&empty_sem, 0, M);
    int init2 = sem_init(&full_sem, 0, 0);
    int init3 = sem_init(&buf, 0, 1);
    if( (init1 != 0) && (init2 != 0) && (init3 != 0))
    {
        printf("sem init failed \n");
        exit(1);
    }
}

void print()
{
    int i;
    for(i = 0; i < M; ++i)
        printf("%d ", buff[i]);
    printf("\n");
}

void *producer(void *arg)
{
    while(1)
    {
        P(buf);
        P(empty_sem);
        
        in = in % M;
        printf("(+)produce a product. buffer:");

        buff[in++] = 1;
        print();
        
        V(full_sem);
        V(buf);
    }
    return NULL;
}

void *consumer(void *arg)
{
    while(1)
    {
        P(buf);
        P(full_sem);
        
        out = out % M;
        printf("(-)consume a product. buffer:");

        buff[out++] = 0;
        print();
        
        V(empty_sem);
        V(buf);
    }
    return NULL;
}

int main()
{
    pthread_t id1[N];
    pthread_t id2[N];

    sem_mutex_init();
    
    for(int i = 0; i < N; ++i)
        pthread_create(&id1[i], NULL, producer, NULL);
    
    for(int i = 0; i < N; ++i)
        pthread_create(&id2[i], NULL, consumer, NULL);

    sem_destroy(&empty_sem);
    sem_destroy(&full_sem);
    sem_destroy(&buf);
    for(int i = 0; i < N; ++i)
        pthread_join(id1[i],NULL);
    for(int i = 0; i < N; ++i)
        pthread_join(id2[i],NULL);

    return 0;
}
