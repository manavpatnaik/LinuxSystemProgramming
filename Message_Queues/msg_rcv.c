#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

struct msgbuf {
    long mtype;
    char msgtxt[200];
};

int main() {
    struct msgbuf msg;
    int msgid;

    key_t key;

    // Generate Key
    if ((key == ftok("msg_snd.c", 'b')) == -1) {
        perror("Key");
        exit(1);
    }

    printf("RCVKey: %d\n", key);

    // Generate message ID
    if ((msgid=msgget(key, 0644|IPC_CREAT)) == -1) {
        perror("msgid");
        exit(1);
    }

    printf("Message ID: %d\n", msgid);

    for (;;) {
        if (msgrcv(msgid, &msg, sizeof(msg), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
    }

    printf("MESSAGE: %s\n", msg.msgtxt);

    return 0;
}