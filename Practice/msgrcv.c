#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>


struct msgbuf {
    long mtype;
    char mtext[100];
};

int main() {
    struct msgbuf msg;
    int msgid;
    key_t key;

    // Obtain Key
    key = ftok("./msgsnd.c", 'b');
    if (key == -1) {
        perror("Key\n");
        exit(1);
    }

    // Initialize message queue
    msgid = msgget(key, IPC_CREAT|0666);
    if (msgid == -1) {
        perror("Error in msgget.\n");
        exit(1);
    }

    printf("Message queue ID: %d\n", msgid);
    msg.mtype = 1;

    // Read message
    for (;;) {
        int msg_status = msgrcv(msgid, &msg, sizeof(msg), msg.mtype, 0);
        if (msg_status == -1) {
            perror("Error in msgrcv\n");
            exit(1);
        } else {
            printf("Received: %s\n", msg.mtext);
        }
    }
}