#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdint.h>
#include <pthread.h>
#include <string.h>
/* 
    Modifique o exercício 4 para que, ao invés de imprimir o seu PID, cada processo filho imprima "Processo XX criado", onde XX é um identificador único de 1 até nprocs. 
    Em outras palavras, XX deverá ser 1 para o primeiro filho, 2 para o segundo filho, 3 para o terceiro filho, etc... Para realizar essa tarefa, você precisará: 
    (i) criar uma região de memória compartilhada entre os processos (uma variável inteira denominada "id" inicializada com valor 1); 
    (ii) inicializar um semáforo compartilhado entre todos os processos que será utilizado como um mecanismo de exclusão mútua; 
    (iii) fazer com que cada processo filho, entre em uma região crítica, copie o valor da variável "id" para uma variável "id_local", incremente "id" e saia da região crítica. 
    A variável "id_local" deverá conter o identificador único de cada processo.
     Dica: para a criação de uma região de memória compartilhada entre processos, pesquise sobre a chamada de sistema mmap(). 
     Para a criação de um semáforo compartilhado entre processos, pesquisa sobre as funções sem_open() e sem_unlink().
*/
#define PAGESIZEID sizeof(int)
#define PAGESIZESEM sizeof(sem_t)
#define SEMAPHORE "sem"

int main(int argc, char *argv[])
{
    // Memoria Compartilhada para o Identificador
    int *id = mmap(NULL, PAGESIZEID, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *id = 1;

    // Memoria Local do processos
    int id_local;

    // Criação de espaço de Memoria Compartilhada para o Semaphoro
    sem_t *sem = mmap(NULL, PAGESIZESEM, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(sem, 1, 1);

    // Process ID
    pid_t pid;

    // Numero de Processos
    int numberProcs;
    numberProcs = atoi(argv[1]);

    for (int i = 0; i < numberProcs; ++i)
    {
        // Criação do processo pelo pai
        if(pid != 0) pid = fork();
    }
    // Execução da rotina pelos filhos
    if(pid == 0)
    {
        sem_wait(sem);
        id_local = *id;
        printf("Processo %d criado\n", id_local);
        *id = *id + 1;
        sem_post(sem);
    }
}