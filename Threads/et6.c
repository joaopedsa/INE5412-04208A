#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "./funcThreads.h"

/* 
    Implemente o problema do produtor/consumidor usando semáforos.
*/

#define N 10

sem_t lock_prod, lock_cons, cheio, vazio;
int buffer[N], i = 0, f = 0;

int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        int numberOfThreads = atoi(argv[1]);

        // Inicializa os sem
        sem_init(&lock_prod, 0, 1);
        sem_init(&lock_cons, 0, 1);
        sem_init(&cheio, 0, 0);
        sem_init(&vazio, 0, N);

        printf("Numero de Threads: %s\n", argv[1]);
        // Aloca Memória para as threads
        pthread_t *pthreads = (pthread_t *)malloc(numberOfThreads * sizeof(pthread_t));
        for (int i = 0; i < numberOfThreads; ++i)
        {
            // Cria a thread na posição especifica
            if (i % 2 == 0)
                pthread_create(getAddressThread(pthreads, i), NULL, produtor, NULL);
            else
                pthread_create(getAddressThread(pthreads, i), NULL, consumidor, NULL);
        }
        for (int i = 0; i < numberOfThreads; ++i)
        {
            // espera a thread filha
            pthread_join(getThread(pthreads, i), NULL);
        }

        sem_destroy(&lock_prod);
        sem_destroy(&lock_cons);
        sem_destroy(&cheio);
        sem_destroy(&vazio);

        free(pthreads);
    }
    else
    {
        printf("Insira a quantidade de threads a serem criadas.");
    }

    return 0;
}

void *consumidor(void *arg)
{
    while (1)
    {
        sem_wait(&cheio);
        sem_wait(&lock_cons);
        i = (i + 1) % N;
        buffer[i] = 0;
        sem_post(&lock_cons);
        sem_post(&vazio);
    }
    pthread_exit(NULL);
}

void *produtor(void *arg)
{
    while (1)
    {
        sem_wait(&vazio);
        sem_wait(&lock_prod);
        f = (f + 1) % N;
        buffer[f] = 1;
        sem_post(&lock_prod);
        sem_post(&cheio);
    }
    pthread_exit(NULL);
}

pthread_t *getAddressThread(pthread_t *pthreads, int position)
{
    pthread_t *getAddressThread = pthreads + position;
    return getAddressThread;
}

pthread_t getThread(pthread_t *pthreads, int position)
{
    // pthreads é o endereço da primeira thread
    pthread_t *getThread = pthreads + position;
    return *getThread;
}