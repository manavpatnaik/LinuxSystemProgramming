#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int shmid;
    char* buffer;

    // Initialization
    key_t key = 123456789;
    shmid = shmget(key, 6, IPC_CREAT|0666);
    if (shmid < 0) {
        printf("Shared memory allocation unsuccessful\n");
        shmid = shmget(key, 6, IPC_CREAT|0666);
    }
    printf("======= Shared memory ID: %d =======\n", shmid);

    // Attachment
    buffer = shmat(shmid, NULL, 0);
    if (buffer == NULL) {
        printf("Memory could not be attached\n");
        return -1;
    }

    // Reading data from Shared memory segment
    printf("The data read ==> %s\n", buffer);

    // Detachment 
    int detach_status = shmdt(buffer);
    if (detach_status == -1) {
        printf("Detachment unsuccessful\n");
    } else if (detach_status == 0) {
        printf("Shared memory detached successfully\n");
    }
    return 0;

}