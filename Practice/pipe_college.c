#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int file_pipes[2];
    const char data[] = "Manav";
    pid_t fork_result;
    int data_written;

    if (pipe(file_pipes) == 0) {
        fork_result = fork();
        if (fork_result == -1) {
            printf("Fork failure\n");
            exit(1);
        }

        if (fork_result == 0) {
            close(0);
            dup(file_pipes[0]);
            close(file_pipes[0]);
            close(file_pipes[1]);
            execlp("echo", "echo", NULL);
            exit(1);
        } else {
            close(file_pipes[0]);
            data_written = write(file_pipes[1], data, strlen(data));
            close(file_pipes[1]);
            printf("Process %d wrote - %d bytes\n", getpid(), data_written);
        }
    }
    exit(1);
}