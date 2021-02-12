#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int shmid, retval;
    void* memory;
    char* p;

    shmid = shmget((key_t)123456789, 6, 0666);
    if (shmid < 0){
        printf("Shared memory allocation unsuccessful\n");
        shmid = shmget((key_t)123456789, 6, 0666);
    }

    printf("Shared memory allocated, ID: %d\n", shmid);

    memory = shmat(shmid, NULL, 0);
    if (memory == NULL) {
        printf("Memory attachment unsuccessful\n");
        return 0;
    }
    p = (char *)memory;

    printf("Message: %s\n", p);

    retval = shmdt(p);
    if (retval < 0) {
        printf("Detached");
        return 0;
    }
    return 0;
}