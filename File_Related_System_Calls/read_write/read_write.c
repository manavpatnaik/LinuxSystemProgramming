#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    char buf[100];
    char message[100] = "Hello World, I am working with System calls in Solaris\n";
    fd = open("./my_file.txt", O_RDWR|O_CREAT, 0777);
    printf("File descriptor of 'my_file.txt': %d\n", fd);
    if (fd < 0) {
        perror("File could not be opened\n");
        exit(1);
    } else {
        printf("my_file.txt opened\n");
        write(fd, message, sizeof(message));
        lseek(fd, 0, SEEK_SET);
        read(fd, buf, sizeof(message));
        printf("The value read from the file: %s", buf);
        close(fd);
    }
    return 0;
}