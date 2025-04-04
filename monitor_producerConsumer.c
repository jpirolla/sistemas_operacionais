#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 10  // Tamanho máximo do buffer

// Monitor ProducerConsumer
typedef struct {
    int buffer[N];         // Buffer compartilhado
    int count;             // Número de itens no buffer
    int in, out;           // Índices para inserção e remoção

    pthread_mutex_t mutex; // Mutex para exclusão mútua
    pthread_cond_t full;   // Condição para buffer cheio
    pthread_cond_t empty;  // Condição para buffer vazio
} ProducerConsumer;

// Inicializa o monitor
void init_monitor(ProducerConsumer *pc) {
    pc->count = 0;
    pc->in = 0;
    pc->out = 0;
    pthread_mutex_init(&pc->mutex, NULL);
    pthread_cond_init(&pc->full, NULL);
    pthread_cond_init(&pc->empty, NULL);
}

// Insere um item no buffer
void insert(ProducerConsumer *pc, int item) {
    pthread_mutex_lock(&pc->mutex);

    while (pc->count == N)  // Se o buffer estiver cheio, espera
        pthread_cond_wait(&pc->full, &pc->mutex);

    pc->buffer[pc->in] = item;  // Insere o item no buffer
    pc->in = (pc->in + 1) % N;  // Atualiza o índice circular
    pc->count++;                // Incrementa a contagem de itens

    pthread_cond_signal(&pc->empty); // Sinaliza que há itens disponíveis
    pthread_mutex_unlock(&pc->mutex);
}

// Remove um item do buffer
int remove_item(ProducerConsumer *pc) {
    pthread_mutex_lock(&pc->mutex);

    while (pc->count == 0)  // Se o buffer estiver vazio, espera
        pthread_cond_wait(&pc->empty, &pc->mutex);

    int item = pc->buffer[pc->out];  // Pega o item do buffer
    pc->out = (pc->out + 1) % N;     // Atualiza o índice circular
    pc->count--;                     // Decrementa a contagem de itens

    pthread_cond_signal(&pc->full);  // Sinaliza que há espaço disponível
    pthread_mutex_unlock(&pc->mutex);

    return item;
}
void *producer(void *arg) {
    ProducerConsumer *pc = (ProducerConsumer *)arg;
    int item;

    while (1) {
        item = rand() % 100;  // Produz um item aleatório
        printf("Produzido: %d\n", item);
        insert(pc, item);      // Insere no buffer
    }

    return NULL;
}

void *consumer(void *arg) {
    ProducerConsumer *pc = (ProducerConsumer *)arg;
    int item;

    while (1) {
        item = remove_item(pc);  // Remove do buffer
        printf("Consumido: %d\n", item);
    }

    return NULL;
}

int main() {
    ProducerConsumer pc;
    init_monitor(&pc);

    pthread_t prod_thread, cons_thread;
    pthread_create(&prod_thread, NULL, producer, &pc);
    pthread_create(&cons_thread, NULL, consumer, &pc);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    return 0;
}
