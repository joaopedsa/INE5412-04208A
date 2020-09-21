#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "./funcThreads.h"

/* 
    Tendo como base a solução para o exercício anterior, crie uma variável global do tipo inteiro inicialmente contendo o valor 0 (int contador_global = 0;). 
    Modifique a função executada pelas threads para que cada thread realize 100 operações de incremento nesta variável global (contador_global++;) sem a utilização de mutex.
    Após o término da execução das threads, a main thread deverá imprimir o valor armazenado na variável contador_global. 
    Em uma execução correta, o valor impresso deverá ser igual a 100 vezes o número de threads criadas.
    Execute várias vezes este programa com 2, 4, 8, 32 e 128 threads e observe o valor impresso a cada vez. O que acontece?
*/

// variavel global
int contador_global = 0;

int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        int numberOfThreads = atoi(argv[1]);
        // Aloca Memória e limpa o lixo que estava presente nele
        printf("Numero de Threads: %s\n", argv[1]);
        pthread_t* pthreads = (pthread_t *)malloc(numberOfThreads * sizeof(pthread_t));
        for (int i = 0; i < numberOfThreads; ++i)
        {
            // Cria a thread na posição especifica
            pthread_create(getAddressThread(pthreads, i), NULL, threadRoutine, NULL);
        }
        for (int i = 0; i < numberOfThreads; ++i)
        {
            // espera a thread filha
            pthread_join(getThread(pthreads, i), NULL);
        }
        printf("Finalizou e o valor do contador global é: %d\n", contador_global);
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
    for (int i = 0; i < 100; ++i)
    {
        contador_global++;
    }
    pthread_exit(NULL);
}

pthread_t* getAddressThread(pthread_t *pthreads, int position)
{
    pthread_t* getAddressThread = pthreads + position;
    return getAddressThread;
}

pthread_t getThread(pthread_t *initialThread, int position)
{
    pthread_t* getThread = initialThread + position;
    return *getThread;
}