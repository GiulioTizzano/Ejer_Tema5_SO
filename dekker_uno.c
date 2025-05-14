#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <stddef.h>

int cuenta = 0;
int turno = 0;

void *hilo_uno(void *arg) {
    while(turno != 0) {
        for(int i = 0; i < 100000; i++) {
            cuenta = cuenta + 1;
        }
    }
    turno == 1;
}


void *hilo_dos(void *arg) {
    while(turno != 1) {
        for(int i = 0; i < 100000; i++) {
            cuenta = cuenta - 1;
        }
    }
    turno == 0;
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