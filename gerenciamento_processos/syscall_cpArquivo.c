#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <arquivo_origem> <arquivo_destino>\n", argv[0]);
        return 1;
    }

    int src = open(argv[1], O_RDONLY);
    if (src == -1) {
        perror("Erro ao abrir arquivo de origem");
        return 1;
    }

    int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest == -1) {
        perror("Erro ao criar arquivo de destino");
        close(src);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    while ((bytesRead = read(src, buffer, BUFFER_SIZE)) > 0) {
        if (write(dest, buffer, bytesRead) != bytesRead) {
            perror("Erro ao escrever no arquivo de destino");
            close(src);
            close(dest);
            return 1;
        }
    }

    close(src);
    close(dest);

    printf("Arquivo copiado com sucesso!\n");
    return 0;
}
