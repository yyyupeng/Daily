#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define P(x)    sem_wait(&x)
#define V(x)    sem_post(&x)

sem_t sfork[5];

void *phi(void *arg)
{
    char ch = *(char *)arg;
    int id;
    switch(ch)
    {
    case 'A':
        id = 0;
        break;
    case 'B':
        id = 1;
        break;
    case 'C':
        id = 2;
        break;
    case 'D':
        id = 3;
        break;
    case 'E':
        id = 4;
        break;
    }
    while(1)
    {
        printf("%d 号哲学家在思考...\n", id);
        sleep(1);
        if(id % 2 == 0)
        {
            P(sfork[(id + 1) % 5]);
            printf("%d 号哲学家拿到了右边的筷子!\n", id);
            P(sfork[id]);
            printf("%d 号哲学家拿到了左边的筷子!\n", id);
            printf("%d 号哲学家吃上饭啦!\n", id);
            V(sfork[id]);
            V(sfork[(id + 1) % 5]);
        }
        else
        {
            P(sfork[id]);
            printf("%d 号哲学家拿到了左边的筷子!\n", id);
            P(sfork[(id + 1) % 5]);
            printf("%d 号哲学家拿到了右边的筷子!\n", id);
            printf("%d 号哲学家吃上饭啦!\n", id);
            V(sfork[(id + 1) % 5]);
            V(sfork[id]);
        }
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t A,B,C,D,E; //5个哲学家
    for(int i = 0; i < 5; ++i)
        sem_init(&sfork[i], 0, 1);

    pthread_create(&A, NULL, phi, (void *)"A");
    pthread_create(&B, NULL, phi, (void *)"B");
    pthread_create(&C, NULL, phi, (void *)"C");
    pthread_create(&D, NULL, phi, (void *)"D");
    pthread_create(&E, NULL, phi, (void *)"E");

    for(int i = 0; i < 5; ++i)
        sem_destroy(&sfork[i]);
    pthread_join(A, NULL);
    pthread_join(B, NULL);
    pthread_join(C, NULL);
    pthread_join(D, NULL);
    pthread_join(E, NULL);
    return 0;
}
