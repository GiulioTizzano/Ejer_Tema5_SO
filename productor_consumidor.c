#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <semaphore.h>
#include <pthread.h>

int buffer[5];
int contador = 0;

sem_t mutex;
sem_t semEmpty;
sem_t semFull;

void *productor(void *arg) {
    while(1) {

        // Va a dejar entrar a 5 procesos, luego se bloquea:
        sem_wait(&semEmpty);

        int x = rand() % 100;
        sleep(5);
        // Añadir elemento al buffer
        sem_wait(&mutex);
        buffer[contador] = x;
        contador++;
        sem_post(&mutex);
        sem_post(&semFull);
        
    }
}

void *consumidor(void *arg) {

    while(1) {
        // Quitar del buffer
        sem_wait(&semFull);
        int y;
        // Si el buffer no está vacío => quitar el último elemento del buffer, si está vacío => devolver -1.
        
        sem_wait(&mutex);
        y = buffer[contador - 1];
        contador--;
        sem_post(&mutex);
        sem_post(&semEmpty);
        printf("Número %d \n", y);
        sleep(5);
    }
}

int main() {

    pthread_t productores[10];
    pthread_t consumidores[10];

    sem_init(&mutex, 0, 1);
    sem_init(&semEmpty, 0, 5);
    sem_init(&semFull, 0, 0);


    for(int i = 0; i < 10; i++) {
        pthread_create(&productores[i], NULL, productor, NULL);
        pthread_create(&consumidores[i], NULL, consumidor, NULL);
    }
    
    for(int i = 0; i < 10; i++) {
        pthread_join(productores[i], NULL);
        pthread_join(consumidores[i], NULL);
    }
    return 0;
}