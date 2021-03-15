#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* myfunc(void* arg) {
    int* v = (int *)arg;
    printf("This is the argument: %d\n", *v);
    (*v)++;
    return v;
}

int main() {
    int a = 5;
    void *b;
    pthread_t mythread;
    pthread_create(&mythread, NULL, myfunc, &a);
    pthread_join(mythread, &b);
    printf("This is b: %d\n", *(int *)b);
    printf("Threads done\n");
}