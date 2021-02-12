#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

int main() {
    int i;          // Loop variable
    key_t shmkey;   // key to generate shared memory
    int shmid;      // shared memory ID
    sem_t* sem;     // sync semaphore
    pid_t pid;      // process related   
    int *p;         // this is the shared resource
    unsigned int n; // fork count
    unsigned int value;  // semaphore value

    // Part 1 - create shared memory

    shmkey = ftok("./semaphore.c", 5);
    printf("shmkey for p: %d\n", shmkey);
    shmid = shmget(shmkey, sizeof(int), 0644|IPC_CREAT);
    if (shmid < 0) {
        perror("shmget\n");
        exit(1);
    }

    p = (int *) shmat(shmid, NULL 0);
    *p = 0;
    printf("p is allocated in shared memory, p=%d", *p);

    // Part 2 - forking and semaphore count declaration

    printf("Enter the number of children you want to fork: ");
    scanf("%u", &n);

    printf("Semaphore, binary or counting: ");
    scanf("%u", &value);

    // Part 3 - semaphore initialization

    sem = sem_open("sem_here", O_CREAT|O_EXCL, 0644, value);

    sem_unlink("sem_here");

    printf("semaphore initialized");

    // Part 4 - Forking

    for (i = 0; i < n; i++) {
        pid = fork();
        if (pid < 0) {
            printf("Fork error\n");
        } else if (pid == 0) {
            break; // Child
        }

    } 
    if (pid != 0) {
        while (pid = waitpid(-1, NULL, 0)) {
            if (errno == ECHILD) {
                break;
            }
        }
        printf("All parents exited\n");

        shmdt(p);
        shmctl(shmid, IPC_RMID, 0);

        sem_destroy(sem);
        exit(0);
    } else {
        
    }

}