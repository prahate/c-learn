#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

#define MAX 1

int buffer[MAX];
int fill = 0;
int use = 0;

void put(int value)
{
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
}

int get()
{
    int temp = buffer[use];
    use = (use + 1) % MAX;
    return temp;
}

sem_t empty;
sem_t full;

void *producer(void *arg)
{
    int loops = *(int *)arg;
    int i;
    for (i=0; i < loops; i++)
    {
        printf("putting %d\n", i);
        sem_wait(&empty);
        put(i);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int tmp=0;
    while(tmp != -1)
    {
        sem_wait(&full);
        tmp = get();
        sem_post(&empty);
        printf("%d\n", tmp);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <#loops>", argv[0]);
        exit(0);
    }

    int loops = atoi(argv[1]);
    int rc;

    sem_init(&full, 0, 0);
    sem_init(&empty, 0, MAX);

    pthread_t p1;
    pthread_t c1;

    rc = pthread_create(&p1, NULL, producer, &loops); assert(rc==0);
    rc = pthread_create(&c1, NULL, consumer, NULL); assert(rc==0);

    rc = pthread_join(p1, NULL); assert(rc==0);
    rc = pthread_join(c1, NULL); assert(rc==0);
    exit(EXIT_SUCCESS);
    return 0;
}
