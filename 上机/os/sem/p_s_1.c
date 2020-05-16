#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 6             /*缓冲数目*/
#define P(x)     sem_wait(&x)
#define V(x)    sem_post(&x)

int in = 0;         /*生产者放置产品的位置*/
int out = 0;             /*消费者取产品的位置*/

int buff[M];

sem_t empty_sem;         
sem_t full_sem;         
pthread_mutex_t mutex; 

void sem_mutex_init()
{
    int init1 = sem_init(&empty_sem, 0, M);
    int init2 = sem_init(&full_sem, 0, 0);
    if( (init1 != 0) && (init2 != 0))
    {
        printf("sem init failed \n");
        exit(1);
    }
    
    int init3 = pthread_mutex_init(&mutex, NULL);
    if(init3 != 0)
    {
        printf("mutex init failed \n");
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
        sleep(1);

        P(empty_sem);
        pthread_mutex_lock(&mutex);

        in = in % M;
        printf("(+)produce a product. buffer:");

        buff[in++] = 1;
        print();

        pthread_mutex_unlock(&mutex);
        V(full_sem);
    }
    return NULL;
}

void *consumer(void *arg)
{
    while(1)
    {
        sleep(2);

        P(full_sem);
        pthread_mutex_lock(&mutex);

        out = out % M;
        printf("(-)consume a product. buffer:");

        buff[out++] = 0;
        print();

        pthread_mutex_unlock(&mutex);
        V(empty_sem);
    }
    return NULL;
}

int main()
{
    pthread_t id1;
    pthread_t id2;
    int ret;

    sem_mutex_init();
    
    ret = pthread_create(&id1, NULL, producer, NULL);
    if(ret != 0)
    {
        printf("producer creation failed \n");
        exit(1);
    }
    
    ret = pthread_create(&id2, NULL, consumer, NULL);
    if(ret != 0)
    {
        printf("consumer creation failed \n");
        exit(1);
    }

    sem_destroy(&empty_sem);
    sem_destroy(&full_sem);
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);

    return 0;
}
