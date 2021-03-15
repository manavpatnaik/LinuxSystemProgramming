#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    printf("This is the parent process\n");
    printf("My PID (Parent): %d\n", getpid());
    char *args[] = {"./hello_exec", "Hello", "World", NULL};
    execvp("./hello_exec", args);
    return 0;
}