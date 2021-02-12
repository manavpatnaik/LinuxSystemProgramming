#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    printf("----------Program to open and read from a file----------\n");
    int fd1;
    printf("Opening FILE: new_file.txt");
    fd1 = open("./new_file.txt", O_RDWR|O_CREAT, S_IRWXU);

    chmod("./new_file.txt", 0666);

    if (fd1 < 0) {
        perror("Error while opening file\n");
        exit(1);
    }
    
    printf("File descriptor of the opened file: %d\n", fd1);
    return 0;
}