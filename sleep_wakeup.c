#define N 100  // Tamanho máximo do buffer
#include <stdbool.h> 
int count = 0;  // Número de itens presentes no buffer

void producer(void) {
    int item;

    while (true) {
        item = produce_item();  // Produz um item
        if (count == N) {       // Se o buffer estiver cheio
            sleep();             // Bloqueia o produtor até que o consumidor retire itens
        }
        insert_item(item);      // Insere o item no buffer
        count = count + 1;      // Incrementa o número de itens no buffer
        if (count == 1) {       // Se o buffer estava vazio antes da inserção
            wakeup(consumer);   // Acorda o consumidor para retirar o item
        }
    }
}

void consumer(void) {
    int item;

    while (true) {
        if (count == 0) {         // Se o buffer estiver vazio
            sleep();              // Bloqueia o consumidor até que o produtor insira itens
        }
        item = remove_item();    // Retira o item do buffer
        count = count - 1;       // Decrementa o número de itens no buffer
        if (count == N - 1) {    // Se o buffer estava cheio antes da remoção
            wakeup(producer);    // Acorda o produtor para inserir mais itens
        }
        consume_item(item);      // Consome o item retirado do buffer
    }
}
