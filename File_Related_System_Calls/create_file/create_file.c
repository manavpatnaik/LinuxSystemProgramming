#include <stdio.h>
#include <unistd.h>

int main() {
    int fd1;
    printf("Creating 1 file now\n");
    fd1 = creat("new_file.txt", 0666);
    if (fd1 < 0) {
        perror("File creation error\n");
        exit(1);
    }
    printf("File descriptor of the file created: %d\n", fd1);
    return 0;
}