#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdbool.h>

int cuenta = 0;
volatile bool state[2] = {false, false};

void *hilo_uno(void *arg) {

    for(int i = 0; i < 100000; i++) {
        state[0] = true;
        while(state[1]) {
            state[0] = false;
            sleep(2);
            state[0] = true;
    }
    cuenta += 1;
    state[0] = false;
    }
}


void *hilo_dos(void *arg) {
    for(int i = 0; i < 100000; i++) {
        state[1] = true;
        while(state[0]) {
            state[1] = false;
            sleep(2);
            state[1] = true;
    }
    cuenta -= 1;
    state[1] = false;
    }
}

int main() {

    pthread_t h1;
    pthread_t h2;

    pthread_create(&h1, NULL, hilo_uno, NULL);
    pthread_create(&h2, NULL, hilo_dos, NULL);

    pthread_join(h1, NULL);
    pthread_join(h2, NULL);

    printf("El valor de cuenta final es: %d \n", cuenta);
    return 0;
} 