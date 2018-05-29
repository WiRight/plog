#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void* threadFunc(void* value) {
    while (1) {
        sem_wait(&semaphore);
        int val;
        sem_getvalue(&semaphore, &val);
        printf("%s %d\n", "threadFunc", val);
        // sem_destroy(&semaphore);
        // sem_post(&semaphore);
        // printf("\n%s\n\n", "end");
    }
    printf("end threadFunc\n");
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunc, NULL);

    // semaphore.__align = 2;
    sem_init(&semaphore, 0, 10);
    sem_post(&semaphore);
    printf("sem_post #1\n");
    getchar();

    // semaphore.__align = 5;
    sem_destroy(&semaphore);
    sem_init(&semaphore, 0, 5);
    sem_post(&semaphore);
    printf("sem_post #2\n");
    getchar();

    // semaphore.__align = 10;
    sem_post(&semaphore);
    printf("sem_post #3\n");
    getchar();

    sem_post(&semaphore);
    printf("sem_post #4\n");
    getchar();

    sem_destroy(&semaphore);
    pthread_cancel(thread);

    return 0;
}
