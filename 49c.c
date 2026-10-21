#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int NUM_THREADS = 3;

sem_t resource_semaphore;

// Correct signature: must take void* and return void*
void* use_resource(void* arg){
    long tid = (long)arg;   // cast back to long
    
    printf("Thread %ld is waiting to access a resource.\n", tid);
    
    sem_wait(&resource_semaphore);

    printf("Thread %ld has acquired a resource.\n", tid);
    
    sleep(2);

    printf("Thread %ld is releasing the resource.\n", tid);

    sem_post(&resource_semaphore);

    return NULL;
}

int main() {
   
    sem_init(&resource_semaphore, 0, 2);

    pthread_t threads[NUM_THREADS];

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, use_resource, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&resource_semaphore); 
    return 0;
}
