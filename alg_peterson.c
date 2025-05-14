#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdbool.h>

int cuenta = 0;
int turno = 0;
volatile bool state[2] = {false, false};

void *hilo_uno(void *arg) {

    for(int i = 0; i < 100; i++) {
        
        state[0] = true;
        turno = 1;
        while(state[1] && turno == 1) {
            // NADA
        }
        // Sección crítica
        cuenta += 1;
        state[0] = false;
    }
}


void *hilo_dos(void *arg) {

    for(int i = 0; i < 100; i++) {
        
        state[1] = true;
        turno = 0;
        while(state[0] && turno == 0) {
            // NADA
        }
        // Sección crítica
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