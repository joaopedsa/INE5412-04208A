#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "./funcThreads.h"

/* 
    Com base na solução do Exercício 3, utilize um mutex para resolver o problema da condição de corrida.
*/

// variavel global
int contador_global = 0;

int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        int numberOfThreads = atoi(argv[1]);
        
        // Alocação na memoria para o ponteiro mutex
        pthread_mutex_t* mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));

        // inicializa o mutex no endereço passado
        pthread_mutex_init(mutex, NULL);

        printf("Numero de Threads: %s\n", argv[1]);
        // Aloca Memória para as threads
        pthread_t* pthreads = (pthread_t *)malloc(numberOfThreads * sizeof(pthread_t));
        for (int i = 0; i < numberOfThreads; ++i)
        {
            // Cria a thread na posição especifica
            pthread_create(getAddressThread(pthreads, i), NULL, threadRoutine, mutex);
        }
        for (int i = 0; i < numberOfThreads; ++i)
        {
            // espera a thread filha
            pthread_join(getThread(pthreads, i), NULL);
        }
        printf("Finalizou e o valor do contador global é: %d\n", contador_global);
        
        // Destroi o mutex
        pthread_mutex_destroy(mutex);

        // libera memoria alocada
        free(mutex);
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
    pthread_mutex_t* mutex = (pthread_mutex_t*) arg;
    for (int i = 0; i < 100; ++i)
    {
        pthread_mutex_lock(mutex);
        contador_global++;
        pthread_mutex_unlock(mutex);
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