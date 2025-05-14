#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>


  

int turno = 0;
int cuenta = 0;
void *processA(void *args) {
    while(turno == 1) {}
    for(int i = 0; i < 100; i++) {
        cuenta += 1; 
    }
    turno = 1;
    return NULL;
}

void *processB(void * args) {
    while(turno == 0) {}
    for(int i = 0; i < 100; i++) {
        cuenta -= 1;
    }
    turno = 0;
    return NULL;
}


int main() {
    pthread_t th_a, th_b;

    // Crear los hilos
    pthread_create(&th_a, NULL, processA, NULL);
    pthread_create(&th_b, NULL, processB, NULL);

    // Esperar a que terminen
    pthread_join(th_a, NULL);
    pthread_join(th_b, NULL);

    printf("Valor final de cuenta: %d\n", cuenta);
    return 0;
}
