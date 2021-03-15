#include <stdio.h> 
#include <pthread.h> // Threading library


void *greet(void *arg) { 
    printf("Hello! How are you %s\n", (char *)arg); 
    pthread_exit(NULL); 
} 

int main(void) { 
    pthread_t my_thread_id; 
    pthread_create(&my_thread_id, NULL, greet, "Manav"); 
    pthread_join(my_thread_id, NULL); 
    return 0; 
} 