#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int shmid, retval;
    void* memory;
    char* p;

    shmid = shmget((key_t)123456789, 6, 0666);
    if (shmid < 0) {
        printf("Shared memeory allocation unsuccessful.\n");
        shmid = shmget((key_t)123456789, 6, 0666);
    }
    printf("Shared memory obtained, ID: %d\n", shmid);

    memory = shmat(shmid, NULL, 0);
    if (memory == NULL) {
        printf("Shared memory allocation unsuccessful\n");
        return 0;
    } 
    p = (char *) memory;
    
    // Cleaning the memory
    memset(p, '\0', 6);

    // Writing into the memory
    memcpy(p, "Hello", 6);

    retval = shmdt(p);
    if (retval < 0) {
        printf("Memory detached\n");
        return 0;
    }
    return 0;
}