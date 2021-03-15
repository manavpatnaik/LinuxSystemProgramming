#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fifo_status, fd;
    char data[] = "testdata\n\0";
    fifo_status = mkfifo("/tmp/my_named_pipe", O_WRONLY|O_CREAT);
    fd = open("/tmp/my_named_pipe", O_WRONLY);
    write(fd, data, 10);
    close(fd);
    return 0;
}