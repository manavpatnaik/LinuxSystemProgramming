#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h>
#define NUM_THREADS 5 

char *greetings[NUM_THREADS]; 

void *sayHello(void *threadid) { 
   int *id_ptr, taskid; 
   sleep(1); 
   id_ptr = (int *) threadid; 
   taskid = *id_ptr; 
   printf("Current Thread %d: %s\n", taskid, greetings[taskid]); 
   pthread_exit(NULL); 
} 

int main(int argc, char *argv[]) { 
    pthread_t threads[NUM_THREADS]; 
    int *taskids[NUM_THREADS];  
    int thread_status;
    greetings[0] = "English: Hello World!"; 
    greetings[1] = "French: Bonjour, le monde!"; 
    greetings[2] = "Spanish: Hola al mundo"; 
    greetings[3] = "Klingon: Nuq neH!"; 
    greetings[4] = "German: Guten Tag, Welt!"; 

    for(int i=0; i<NUM_THREADS; i++) {    
        taskids[i] = (int *) malloc(sizeof(int)); 
        *taskids[i] = i; 
        printf("Creating thread %d\n", i+1); 
        thread_status = pthread_create(&threads[i], NULL, sayHello, (void *) taskids[i] ); 
        if (thread_status) { 
            printf("ERROR; return code from pthread_create() is %d\n", thread_status); 
            exit(-1); 
        } 
    } 
    pthread_exit(NULL);  
} 