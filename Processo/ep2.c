#include <stdio.h>
#include <unistd.h>
/* 
    Escreva um programa em C no qual o processo pai cria 4 processos filhos. 
    Para cada filho criado, o processo pai deverá imprimir na tela "Processo pai XX criou YY", onde XX é o PID do pai e YY o PID do filho. 
    Além disso, os processos filhos deverão imprimir na tela "Processo filho XX", onde XX é o PID do filho. 
    Dica: utilize a função getpid() para retornar o PID do processo corrente.
*/

int main(int argc, char *argv[])
{
    pid_t pid;
    pid = fork();
    if (pid != 0) printf("Processo pai %d criou %d\n", pid, getpid());
    for (int i = 0; i < 3; ++i)
    {
        if (pid != 0)
        {
            pid = fork();
            if(pid != 0) printf("Processo pai %d criou %d\n", pid, getpid());
        }
    }

    if (pid == 0) printf("Processo filho %d\n", getpid());
}