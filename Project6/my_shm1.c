#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

#define MAX_TEXT 1024

struct membuf {
    long written;
    char mtext[MAX_TEXT];
};

int main(int argc, char **argv)
{
    void *shm = NULL;
    struct membuf *shared = NULL;
    int mid;
    FILE *fp;
    mid = shmget((key_t)0314, sizeof(struct membuf), 0666|IPC_CREAT);
    if (mid == -1)
    {
        perror("shmget failed");
        return EXIT_FAILURE;
    }

    shm = shmat(mid, (void *)0, 0);
    if (shm == (void *)-1)
    {
        perror("shmat failed");
        return EXIT_FAILURE;
    }

    shared = (struct membuf *)shm;

    fp = fopen("testcase/datam.txt", "r");
    fgets(shared->mtext, BUFSIZ, fp);
    shared->written = 1;

    if (shmdt(shm) == -1)
    {
        perror("shmdt failed");
        return EXIT_FAILURE;
    }

    sleep(1);
    return EXIT_SUCCESS;
}