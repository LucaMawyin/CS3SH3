#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_COUNT 10
#define DEPOSIT_THREADS 7
#define WITHDRAW_THREADS 3

int amount = 0;
pthread_mutex_t mutex;
sem_t can_deposit;
sem_t can_withdraw;

void *deposit(void *arg)
{
    int value = *(int *)arg;

    printf("Executing deposit function\n");

    sem_wait(&can_deposit);
    pthread_mutex_lock(&mutex);

    amount += value;
    printf("Deposit amount = %d\n", amount);

    pthread_mutex_unlock(&mutex);
    sem_post(&can_withdraw);

    return NULL;
}

void *withdraw(void *arg)
{
    int value = *(int *)arg;

    printf("Executing withdraw function\n");

    sem_wait(&can_withdraw);
    pthread_mutex_lock(&mutex);

    amount -= value;
    printf("Withdraw amount = %d\n", amount);

    pthread_mutex_unlock(&mutex);
    sem_post(&can_deposit);

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2 || atoi(argv[1]) != 100)
    {
        fprintf(stderr, "Usage: %s 100\n", argv[0]);
        return 1;
    }

    int value = atoi(argv[1]);

    pthread_t threads[THREAD_COUNT];

    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        fprintf(stderr, "Error initializing mutex\n");
        return 1;
    }

    if (sem_init(&can_deposit, 0, 4) != 0)
    {
        fprintf(stderr, "Error initializing deposit semaphore\n");
        pthread_mutex_destroy(&mutex);
        return 1;
    }

    if (sem_init(&can_withdraw, 0, 0) != 0)
    {
        fprintf(stderr, "Error initializing withdraw semaphore\n");
        sem_destroy(&can_deposit);
        pthread_mutex_destroy(&mutex);
        return 1;
    }

    for (int i = 0; i < DEPOSIT_THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, deposit, &value) != 0)
        {
            fprintf(stderr, "Error creating deposit thread\n");
            break;
        }
    }

    for (int i = DEPOSIT_THREADS; i < THREAD_COUNT; i++)
    {
        if (pthread_create(&threads[i], NULL, withdraw, &value) != 0)
        {
            fprintf(stderr, "Error creating withdraw thread\n");
            break;
        }
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Final amount = %d\n", amount);

    sem_destroy(&can_deposit);
    sem_destroy(&can_withdraw);
    pthread_mutex_destroy(&mutex);

    return 0;
}