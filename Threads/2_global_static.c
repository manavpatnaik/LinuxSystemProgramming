#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 

// Global variable to be modified in threads
int glbl = 0;

void* my_thread(void *yargp) {
    int* myid = (int *)yargp;
    static int s = 0;
    
    // Observing changes to the static variable
    ++s;
    ++glbl;
    printf("THread ID: %d, Static: %d, Global: %d\n", *myid, s, glbl);
    return NULL;
}

int main() {
    pthread_t my_thread_id;
    // Creating 5 threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&my_thread_id, NULL, my_thread, (void *)my_thread_id);
    }
    pthread_join(my_thread_id, NULL);
    pthread_exit(NULL);
    return 0;
}