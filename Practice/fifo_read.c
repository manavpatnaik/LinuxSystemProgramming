#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd;
    char data[10];
    fd = open("/tmp/my_named_pipe", O_RDONLY);
    read(fd, data, 10);
    write(1, data, 10);
    return 0;
}