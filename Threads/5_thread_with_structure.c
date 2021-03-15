#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 

struct Person { 
    char* name; 
    int age; 
}; 

void *displayInfo(void *person) { 
    printf("Name: %s\n", ((struct Person*)person)->name); 
    printf("Age: %d\n", ((struct Person*)person)->age); 
} 

 

int main() { 
    struct Person *Manav = (struct Person *)malloc(sizeof(struct Person)); 
    char manav[] = "Manav"; 
    Manav->name = manav; 
    Manav->age = 20; 

    pthread_t my_thread_id; 
    pthread_create(&my_thread_id, NULL, displayInfo, (void *)Manav); 
    pthread_join(my_thread_id, NULL); 
    return 0; 

} 