#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 25

struct msgbuf {
    long mtype;
    char mtext[MAX_TEXT];
};

int main(void){
    int qid;
    struct msgbuf wrbuf;
    FILE *fp = fopen("testcase/data.txt", "r");
    if(fp == NULL){
        printf("Failed to open file\n");
        return 1;
    }
    qid = msgget((key_t)0314, IPC_CREAT | 0666);
    if(qid == -1){
        perror("Failed in calling msgget");
        return (-1);
    }
    while(fgets(wrbuf.mtext, 25, fp) > 0){
        wrbuf.mtype = 996;
        if (msgsnd(qid, (void *)&wrbuf, MAX_TEXT, 0) == -1)
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
    }
    sleep(1);
    return EXIT_SUCCESS;
}