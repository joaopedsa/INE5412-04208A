#include <stdio.h>
#include <unistd.h>
/* 
    Escreva um programa em C no qual o processo pai cria 2 processos filhos e cada um dos processos filhos cria mais 2 processos filhos. 
    Os processos filhos deverão imprimir na tela "Processo XX filho de YY", onde XX é o PID do processo e YY é o PID do pai do processo. 
    Dica: utilize a função getpid() para retornar o PID do processo corrente e getppid() para retornar o PID do pai do processo corrente.
*/

int main(int argc, char *argv[])
{
    pid_t pid;
    // Processo Pai cria 2 Filhos
    pid = fork();
    if(pid != 0) pid = fork();

    // Os 2 Processos Filhos Criam 2 Filhos Cada
    if(pid == 0)
    {
        pid = fork();
        if(pid != 0)
         pid = fork();
    }
    
    if(pid == 0) printf("Processo %d filho de %d \n", getpid(), getppid());
}