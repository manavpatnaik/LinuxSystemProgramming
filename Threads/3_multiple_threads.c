#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> // THreading library

void* mythread_1(void *yargp) {
    printf("THread 1 running\n");
    for (int i = 0; i < 3; i++) {
        sleep(1);
        printf("Timer inside thread 1: %d\n", i+1);
    }
    printf("Thread 1 complete\n");
    return NULL;
}

void* mythread_2(void *yargp) {
    printf("Thread 2 running\n");
    for (int i = 0; i < 3; i++) {
        sleep(1);
        printf("Timer inside thread 2: %d\n", i+1);
    }
    printf("Thread 2 complete\n");
    return NULL;
}

int main() {
    pthread_t my_thread_id_1, my_thread_id_2;
    pthread_create(&my_thread_id_1, NULL, mythread_1, NULL);
    pthread_create(&my_thread_id_2, NULL,  mythread_2, NULL);

    // Waiting for both threads to end
    pthread_join(my_thread_id_1, NULL);
    pthread_join(my_thread_id_2, NULL);

    printf("Both threads completed\n");
    return 0;
}