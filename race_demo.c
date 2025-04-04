/*
 * race_demo.c
 * Demonstra uma condição de disputa incrementando uma variável global
 * sem proteção, e depois com um mutex (pthread_mutex_t).
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define ITERATIONS 1000000

long shared_counter = 0;
pthread_mutex_t lock;

void* increment_without_lock(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        // Acesso sem exclusão mútua
        shared_counter++;
    }
    return NULL;
}

void* increment_with_lock(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        // Acesso protegido
        pthread_mutex_lock(&lock);
        shared_counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // --- Parte 1: Sem exclusão mútua ---
    shared_counter = 0;
    printf("Sem Mutex:\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_without_lock, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Valor final esperado: %d\n", NUM_THREADS * ITERATIONS);
    printf("Valor final obtido: %ld\n\n", shared_counter);

    // --- Parte 2: Com exclusão mútua ---
    pthread_mutex_init(&lock, NULL);
    shared_counter = 0;

    printf("Com Mutex:\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_with_lock, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Valor final esperado: %d\n", NUM_THREADS * ITERATIONS);
    printf("Valor final obtido: %ld\n", shared_counter);

    pthread_mutex_destroy(&lock);
    return 0;
}
