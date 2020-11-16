#include <stddef.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TEXT 1024

struct membuf {
    long written;
    char mtext[MAX_TEXT];
};

int main(int argc, char **argv)
{
    void *shm = NULL;
    struct membuf *shared; 
    int mid;
    
    mid = shmget((key_t)0314, sizeof(struct membuf), 0666 | IPC_CREAT);
    if (mid == -1)
    {
        perror("shmat failed");
        return EXIT_FAILURE;
    }
    
    shm = shmat(mid, 0, 0);
    if (shm == (void *)-1)
    {
        perror("shmat failed");
        return EXIT_FAILURE;
    }

    shared = (struct membuf*)shm;


    if (shared->written == 1)
        printf("The message is: %s", shared->mtext);
    shared->written = 0;

    if (shmdt(shm) == -1)
    {
        perror("shmdt failed");
        return EXIT_FAILURE;
    }
    
    if (shmctl(mid, IPC_RMID, 0) == -1)
    {
        perror( "shmctl failed");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}