#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int recurso = 0;
int read_count = 0;

sem_t mutex;        // protects read_count
sem_t recurso_lock; // controls access to the shared resource

void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&recurso_lock); // first reader blocks writers
        }
        sem_post(&mutex);

        // 🔵 Critical Section (Read)
        printf("🟢 Reader %ld reads value: %d\n", (long)pthread_self(), recurso);
        sleep(1);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&recurso_lock); // last reader unblocks writers
        }
        sem_post(&mutex);

        sleep(1); // rest between reads
    }
    return NULL;
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&recurso_lock); // exclusive access

        // 🔴 Critical Section (Write)
        recurso++;
        printf("🔴 Writer %ld wrote value: %d\n", (long)pthread_self(), recurso);
        sleep(2);

        sem_post(&recurso_lock); // release resource

        sleep(2); // rest between writes
    }
    return NULL;
}

int main() {
    pthread_t lectores[5], escritores[2];

    sem_init(&mutex, 0, 1);
    sem_init(&recurso_lock, 0, 1);

    for (int i = 0; i < 5; i++) {
        pthread_create(&lectores[i], NULL, reader, NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_create(&escritores[i], NULL, writer, NULL);
    }

    for (int i = 0; i < 5; i++) pthread_join(lectores[i], NULL);
    for (int i = 0; i < 2; i++) pthread_join(escritores[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&recurso_lock);

    return 0;
}
