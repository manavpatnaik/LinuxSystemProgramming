#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int pipes[2];
    int process;
    char data[100];

    pipe(pipes);

    process = fork();

    if (process > 0) {
        fflush(stdin);
        printf("Parent Process\n");
        write(pipes[1], "HelloWorld\n\0", 12);
    } else if (process == 0) {
        sleep(5);
        fflush(stdin);
        printf("Child Process\n");
        read(pipes[0], data, 12);
        write(1, data, 12);
    }
    return 0;
}