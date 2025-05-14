#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex_uno;
sem_t mutex_dos;
sem_t mutex_tres;
pthread_t hilo_uno;
pthread_t hilo_dos;
pthread_t hilo_tres;


void *escribirA(void *args) {
    
    sem_wait(&mutex_uno);
    printf("A \n");
    sem_post(&mutex_dos);


}

void *escribirB(void *args) {
    sem_wait(&mutex_dos);
    printf("B \n");
    sem_post(&mutex_tres);
}

void *escribirC(void *args) {
    sem_wait(&mutex_tres);
    printf("C \n");
    sem_post(&mutex_uno);
}





int main() {

    sem_init(&mutex_uno, 0, 1);
    sem_init(&mutex_dos, 0, 0);
    sem_init(&mutex_tres, 0, 0);


    for(int i = 0; i < 6; i++) {
        pthread_create(&hilo_uno, NULL, escribirA, NULL);
        pthread_create(&hilo_dos, NULL, escribirB, NULL);
        pthread_create(&hilo_tres, NULL, escribirC, NULL);
    }
    // pthread_create(&hilo_uno, NULL, escribirA, NULL);
    // pthread_create(&hilo_dos, NULL, escribirB, NULL);
    // pthread_create(&hilo_tres, NULL, escribirC, NULL);

    pthread_join(hilo_uno, NULL);
    pthread_join(hilo_dos, NULL);
    pthread_join(hilo_tres, NULL);

    return 0;
}