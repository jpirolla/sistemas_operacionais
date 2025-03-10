#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        printf("Sou o processo filho, PID: %d\n", getpid());
    } else {
        printf("Sou o processo pai, PID: %d, filho PID: %d\n", getpid(), pid);
        wait(NULL);  // O pai espera o filho
    }

    return 0;
}
