#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/* 
    Transforme o código do exercício anterior em um código genérico que cria n threads. 
    Da mesma forma que o exercício anterior, a main thread deverá aguardar a finalização de todas as worker threads antes de terminar.
    O número de threads deverá ser definido via linha de comando.
*/

void *threadRoutine(void *arg)
{
    pthread_t tid = pthread_self();
    printf("Nova thread criada.TID = %u!\n", (unsigned int)tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        int numberOfThreads = atoi(argv[1]);
        pthread_t pthread[numberOfThreads];
        printf("Numero de Threads: %s\n", argv[1]);
        for (int i = 0; i < numberOfThreads; ++i)
        {
            pthread_create(&pthread[i], NULL, threadRoutine, NULL);
        }
        for (int i = 0; i < numberOfThreads; ++i)
        {
            pthread_join(pthread[i], NULL);
        }
        printf("Finalizou\n");
    }
    else
    {
        printf("Insira a quantidade de threads a serem criadas.");
    }

    return 0;
}