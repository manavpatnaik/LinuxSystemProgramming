#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

struct vote {
    long msg_type;
    int contestant_voted_for;
};

int main() {
    struct vote vote_to_be_cast;
    int msgid;
    key_t key;

    // Generate Key
    key = ftok("polling_officer.c", 'b');
    if (key == -1) {
        perror("Key generation Error");
        exit(1);
    }

    // Generate message ID
    if ((msgid=msgget(key, 0666|IPC_CREAT)) == -1) {
        perror("Error in msgid");
        exit(1);
    }
    
    printf("Hello Voter!\n");
    
    // Casting vote
    do {
        printf("Enter your vote, A number between 1 and 3:\n");
        scanf("%d", &vote_to_be_cast.contestant_voted_for);
        printf("Mtype: %d\n", vote_to_be_cast.contestant_voted_for);
    } while (vote_to_be_cast.contestant_voted_for < 1 || vote_to_be_cast.contestant_voted_for > 3);

    vote_to_be_cast.msg_type = 1;

    // Sending vote
    msgsnd(msgid, &vote_to_be_cast, sizeof(vote_to_be_cast), 0);
    printf("Your vote has been cast!\n");
    
    return 0;
}