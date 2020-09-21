#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "./funcThreads.h"

/* 
    Substitua o mutex da solução anterior por um semáforo. Verifique se o comportamento com semáforo é equivalente ao do mutex.
*/

// variavel global
int contador_global = 0;

int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        int numberOfThreads = atoi(argv[1]);
        
        // Alocação na memoria para o ponteiro mutex
        sem_t* sem = (sem_t*)malloc(sizeof(sem_t));

        // inicializa o semaforo aberto com o endereço passado
        sem_init(sem, 0, 1);

        printf("Numero de Threads: %s\n", argv[1]);
        // Aloca Memória para as threads
        pthread_t* pthreads = (pthread_t*)malloc(numberOfThreads * sizeof(pthread_t));
        for (int i = 0; i < numberOfThreads; ++i)
        {
            // Cria a thread na posição especifica
            pthread_create(getAddressThread(pthreads, i), NULL, threadRoutine, sem);
        }
        for (int i = 0; i < numberOfThreads; ++i)
        {
            // espera a thread filha
            pthread_join(getThread(pthreads, i), NULL);
        }
        printf("Finalizou e o valor do contador global é: %d\n", contador_global);
        
        // Destroi o mutex
        sem_destroy(sem);

        // libera memoria alocada
        free(sem);
        free(pthreads);
    }
    else
    {
        printf("Insira a quantidade de threads a serem criadas.");
    }

    return 0;
}

void *threadRoutine(void *arg)
{
    sem_t* sem = (sem_t*) arg;
    for (int i = 0; i < 100; ++i)
    {
        sem_wait(sem);
        contador_global++;
        sem_post(sem);
    }
    pthread_exit(NULL);
}

pthread_t* getAddressThread(pthread_t *pthreads, int position)
{
    pthread_t* getAddressThread = pthreads + position;
    return getAddressThread;
}

pthread_t getThread(pthread_t *pthreads, int position)
{
    // pthreads é o endereço da primeira thread
    pthread_t* getThread = pthreads + position;
    return *getThread;
}