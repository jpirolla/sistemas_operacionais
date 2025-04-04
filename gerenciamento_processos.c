/*
 * Descrição: Este programa cria múltiplos processos filhos (NUM_PROCESSES) e os faz executar
 *           o comando "ls" via execl(). O processo pai aguarda a finalização de todos os filhos
 *           e exibe suas respectivas terminações.
 * 
 * Como executar: `gcc -o processos gerenciamento_processos.c`
 *                `./processos`
 * 
 * Informações adicionais: Utilize `time strace -c ./processos` para obter as estatisticas
 */


#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h> 

#define NUM_PROCESSES 2

void run_task(int id) {
    printf("\nProcesso Filho %d iniciado (PID: %d)\n", id, getpid());
    printf("Processo fiho %d executando ls...\n", id);

    // o processo agora passa a ser ls 
    execl("/bin/ls", "ls", (char *)NULL); 
    printf("Processo Filho %d finalizado (PID: %d)\n", id, getpid());
}

int main() {
    pid_t pid;
    int status;

    // loop para criar multiplos processos filhos
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pid = fork();

        if (pid == 0) {
            run_task(i); // filho executa run_task 
            exit(0);     
        }
    }

    // pai espera os filhos terminarem
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pid = wait(&status);  // aguarda retornar com status 0 indicando que finalizou 
        if (pid > 0) {
            printf("Processo Filho PID: %d terminou com status: %d\n", pid, status);
        }
    }
    printf("Todos os filhos terminaram. Processo pai finalizado.\n");
    printf("\n\n");
    return 0;
}