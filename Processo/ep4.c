#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
/* 
    Escreva um programa em C que recebe via linha de comando a quantidade de processos a serem criados (procs). 
    O processo principal (processo pai) cria procs processos filhos com uso da chamada de sistema fork(). 
    Cada processo filho deverá ficar bloqueado durante um tempo aleatório entre 1s e 10s e deverá imprimir "Processo XX criado", onde XX é o PID do processo.
    Utilize as chamadas de sistema sleep() e getpid() para resolver esse exercício.
*/

int main(int argc, char *argv[])
{
    pid_t pid;
    int numberProcs;
    numberProcs = atoi(argv[1]);
    for (int i = 0; i < numberProcs; ++i)
    {
        if(pid != 0) pid = fork();
    }
    if(pid == 0) 
    {
        sleep((rand() % 9) + 1);
        printf("Processo %d criado \n", getpid());
    }

}