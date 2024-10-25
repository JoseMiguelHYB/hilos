#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

// Función que ejecutará cada hilo
void* print_hello(void* thread_id) {
    long tid = (long)thread_id;  // Convertimos el argumento a un identificador de hilo
    printf("Hilo #%ld: Mi ID es %lu\n", tid, pthread_self());
    
    // Devolvemos el identificador del hilo como valor de retorno
    pthread_exit((void*) tid);
}

int main() {
    pthread_t threads[NUM_THREADS];  // Array para almacenar los identificadores de los hilos
    int rc;
    long t;
    void* status;
    
    // Crear varios hilos
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creando hilo #%ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_hello, (void*)t);
        
        if (rc) {
            printf("Error al crear el hilo #%ld. Código de error: %d\n", t, rc);
            exit(-1);
        }
    }

    // Esperar la terminación de cada hilo y obtener su valor de retorno
    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_join(threads[t], &status);
        if (rc) {
            printf("Error al unir el hilo #%ld. Código de error: %d\n", t, rc);
            exit(-1);
        }
        printf("Hilo #%ld terminó con valor de retorno %ld\n", t, (long)status);
    }

    printf("Programa principal terminó.\n");
    pthread_exit(NULL);
}
