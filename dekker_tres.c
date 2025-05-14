#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int flag[2] = {0, 0};
int cuenta; 
int turno = 0;

void* hilo_ingresar(void* arg) {
    for (int i = 0; i < 100000; ++i) {
        flag[0] = 1;
        while (flag[1]) {
            if (turno == 1) {
                flag[0] = 0;
                while (turno == 1);
                flag[0] = 1;
            }
        }
        cuenta += 1;
        turno = 1;
        flag[0] = 0;
    }
    return NULL;
}

void* hilo_retirar(void* arg) {
    for (int i = 0; i < 100000; ++i) {
        flag[1] = 1;
        while (flag[0]) {
            if (turno == 0) {
                flag[1] = 0;
                while (turno == 0);
                flag[1] = 1;
            }
        }
        cuenta -= 1;
        turno = 0;
        flag[1] = 0;
    }
    return NULL;
}


int main(){

    pthread_t ingresar , retirar;

    pthread_create(&ingresar , NULL , hilo_ingresar, NULL);
    pthread_create(&retirar , NULL , hilo_retirar, NULL);

    pthread_join(ingresar, NULL);
    pthread_join(retirar, NULL);

    printf("Este es el valor de la cuenta tras las operaciones: %d\n" , cuenta);
    return 0;
}