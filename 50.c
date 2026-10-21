#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semA;
sem_t semB;

void* thread_one_func(void* arg) {
    printf("Thread 1: Trying to acquire semA...\n");
    sem_wait(&semA);
    printf("Thread 1: Acquired semA!\n");

    sleep(1);

    printf("Thread 1: Trying to acquire semB...\n");
    sem_wait(&semB);
    printf("Thread 1: Acquired semB!\n");

    sem_post(&semB);
    sem_post(&semA);

    return NULL;
}

void* thread_two_func(void* arg) {
    printf("Thread 2: Trying to acquire semB...\n");
    sem_wait(&semB);
    printf("Thread 2: Acquired semB!\n");

    sleep(1);

    printf("Thread 2: Trying to acquire semA...\n");
    sem_wait(&semA);
    printf("Thread 2: Acquired semA!\n");

    sem_post(&semA);
    sem_post(&semB);

    return NULL;
}

int main() {
    sem_init(&semA, 0, 1);
    sem_init(&semB, 0, 1);

    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread_one_func, NULL);
    pthread_create(&t2, NULL, thread_two_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&semA);
    sem_destroy(&semB);

    return 0;
}
