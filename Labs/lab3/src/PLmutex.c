#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 6

int amount = 0;
pthread_mutex_t mutex;

void *deposit(void *arg)
{
    int value = *(int *)arg;

    pthread_mutex_lock(&mutex);

    amount += value;
    printf("Deposit amount = %d\n", amount);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *withdraw(void *arg)
{
    int value = *(int *)arg;

    pthread_mutex_lock(&mutex);

    amount -= value;
    printf("Withdrawal amount = %d\n", amount);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <deposit_amount> <withdraw_amount>\n", argv[0]);
        return 1;
    }

    int deposit_amount = atoi(argv[1]);
    int withdraw_amount = atoi(argv[2]);

    printf("Deposit amount: %d\n", deposit_amount);
    printf("Withdrawal amount: %d\n", withdraw_amount);

    pthread_t threads[THREAD_COUNT];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < THREAD_COUNT / 2; i++)
    {
        pthread_create(&threads[i], NULL, deposit, &deposit_amount);
    }

    for (int i = THREAD_COUNT / 2; i < THREAD_COUNT; i++)
    {
        pthread_create(&threads[i], NULL, withdraw, &withdraw_amount);
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Final amount = %d\n", amount);

    pthread_mutex_destroy(&mutex);

    return 0;
}