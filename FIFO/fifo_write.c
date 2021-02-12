#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, retval;
    char buffer[8] = "testdata";
    fflush(stdin);
    retval = mkfifo("/tmp/myfifo", 0666);
    fd = open("/tmp/myfifo", O_WRONLY);
    write(fd, buffer, sizeof(buffer));
    close(fd);
    return 0;
}