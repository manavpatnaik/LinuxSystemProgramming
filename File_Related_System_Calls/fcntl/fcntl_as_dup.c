#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd1, fd2;
    printf("Creating a new file: new_file.txt\n");
    fd1 = open("new_file.txt", O_CREAT|O_RDONLY, 0777);
    fd2 = fcntl(fd1, F_DUPFD, 0);
    printf("FD1: %d, FD2: %d\n", fd1, fd2);
    while(1){}
    return 0;
}