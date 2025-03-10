#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h> 

#define NUM_PROCESSES 4

void run_task(int id) {
    printf("\nProcesso Filho %d iniciado (PID: %d)\n", id, getpid());
    printf("Processo fiho %d executando ls...\n", id);
    execl("/bin/ls", "ls", (char *)NULL);  // ou usar o sleep()
    printf("Processo Filho %d finalizado (PID: %d)\n", id, getpid());
}

int main() {
    pid_t pid;
    int status;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pid = fork();
        if (pid == 0) {
            run_task(i);  // Filho executa a tarefa
            exit(0);  // termino do filho
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