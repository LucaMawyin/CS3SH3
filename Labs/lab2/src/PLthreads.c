#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2
#define LIST_SIZE 20

int list[LIST_SIZE] = {
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
};

int sum = 0;

typedef struct
{
    int from_index;
    int to_index;
} parameters;

void *runner(void *param)
{
    parameters *data = (parameters *)param;

    int from = data->from_index;
    int to = data->to_index;

    for (int i = from; i <= to; i++)
    {
        sum += list[i];
    }

    free(data);
    pthread_exit(0);
}

int main(void)
{
    pthread_t workers[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        parameters *data = (parameters *)malloc(sizeof(parameters));

        data->from_index = i * (LIST_SIZE / NUM_THREADS);
        data->to_index = (i + 1) * (LIST_SIZE / NUM_THREADS) - 1;

        pthread_create(&workers[i], &attr, runner, data);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(workers[i], NULL);
    }

    printf("Sum of numbers in the list is: %d\n", sum);

    return 0;
}