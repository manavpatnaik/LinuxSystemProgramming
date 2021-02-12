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
    
    printf("SNDKey: %d\n", key);

    // Generate message ID
    if ((msgid=msgget(key, 0644|IPC_CREAT)) == -1) {
        perror("msgid");
        exit(1);
    }

    printf("The message ID: %d\n", msgid);
    printf("Enter text: ");

    msg.mtype = 1;

    while (gets(msg.msgtxt), !feof(stdin)) {
        if (msgsnd(msgid, &msg, sizeof(msg), 0) == -1) {
            perror("msgsnd");
            exit(1); 
        }
    }

    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}