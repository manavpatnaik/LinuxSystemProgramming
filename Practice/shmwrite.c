#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    int shmid;
    void* memory;
    char* p;

    // Initialization
    key_t key = 123456789;
    shmid = shmget(key, 6, IPC_CREAT|0666);
    if (shmid < 0) {
        printf("Shared memory allocation unsuccessful\n");
        shmid = shmget(key, 6, IPC_CREAT|0666);
    }
    printf("======= Shared memory ID: %d =======\n", shmid);

    // Attachment
    memory = shmat(shmid, NULL, 0);
    if (memory == NULL) {
        printf("Memory could not be attached\n");
        return -1;
    }
    p = (char *) memory;

    // Writing data into Shared memory
    memset(p, 6, '\0');
    memcpy(p, "Manav", 6);

    // Detachment
    int detach_status = shmdt(p);
    if (detach_status == -1) {
        printf("Detachment unsuccessful\n");
    } else if (detach_status == 0) {
        printf("Shared memory detached successfully\n");
    }
    return 0;
}