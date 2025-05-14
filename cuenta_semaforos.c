#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <semaphore.h>
#include <pthread.h>

int cuenta = 0;
sem_t bin;

void *hilo_uno(void *arg) {

    for(int i = 0; i < 100000; i++) {
        sem_wait(&bin);
    cuenta += 1;
    sem_post(&bin);
    }
}


void *hilo_dos(void *arg) {

    for(int i = 0; i < 100000; i++) {
        sem_wait(&bin);
    cuenta -= 1;
    sem_post(&bin);
    }
}

int main() {

    pthread_t ph_a;
    pthread_t ph_b;
    sem_init(&bin, 0, 1);
    
    pthread_create(&ph_a, NULL, hilo_uno, NULL);
    pthread_create(&ph_b, NULL, hilo_dos, NULL);

    pthread_join(ph_a, NULL);
    pthread_join(ph_b, NULL);

    printf("El valor de la cuenta es: %d \n", cuenta);

    return 0;
}