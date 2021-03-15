#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> // THreading library

// C function that will be executed as a thread
void *sayHello(void* j) {
    // To print after a delay of 1 second
    sleep(1);
    printf("Hello, this is a thread\n");
    return NULL;
}

int main() {
    // Declaring a thread
    pthread_t my_thread_id;
    printf("Before the thread execution\n");

    // Creating a thread
    pthread_create(&my_thread_id, NULL, sayHello, NULL);
    
    // Make the program wait for the termination of the above thread
    pthread_join(my_thread_id, NULL);

    printf("Thread execution complete\n");

    return 0;
}