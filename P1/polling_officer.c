#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

struct vote {
    long msg_type;
    int contestant_voted_for;
};

int max_votes(int* contestants, int n) {
    int max = contestants[0];
    int contestant_number = 0;
    for (int i = 1; i < n; i++) {
        if (contestants[i] > max) {
            max = contestants[i];
            contestant_number = i;
        }
    }
    return contestant_number;
}

int main() {
    int msgid;
    struct vote vote_received;
    key_t key;

    int voters = 5; // 5 voters in total

    // Initializing the contestants
    // contestants[0] - Contestant 1
    // contestants[1] - Contestant 2
    // contestants[2] - Contestant 3
    int contestants[3];
    for (int i = 0; i < 3; i++) contestants[i] = 0;

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

    printf("Welcome polling officer!\n");

    int recv_status, contestant_number;
    // Receive 5 votes
    for (int i = 0; i < voters; i++) {
        // Receiving vote for contestant
        recv_status = msgrcv(msgid, &vote_received, sizeof(vote_received), 0, 0);
        if (recv_status == -1) {
            perror("Error => Contestant 1 Vote");
            exit(1);
        } else {
            contestant_number = vote_received.contestant_voted_for;
            if (contestant_number >= 1 && contestant_number <= 3) {
                contestants[contestant_number-1]++;
                printf("Vote received for contestant %d\n", contestant_number);
            }
        } 
    }

    int winner = max_votes(contestants, 3);
    printf("The winner is: Contestant %d\n", winner+1);

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}