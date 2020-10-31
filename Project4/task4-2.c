#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *PrintInt(void *nump) {
    int *num = (int *)nump;
    printf("The integer argument is %d in thread #%ld!\n", *num, (long)pthread_self());
    pthread_exit(NULL);
}

void *PrintChar(void *chp) {
    char *ch = (char *)chp;
    printf("The character argument is %c in thread #%ld!\n", *ch, (long)pthread_self());
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t myThread1, myThread2;
    int rc, num = 1024, *nump;
    char ch = 'C', *chp;
    nump = &num;
    chp = &ch;
    rc = pthread_create(&myThread1, NULL, PrintInt, (void *)nump);
    if (rc) {
        perror("Failed in calling pthread_create");
        exit(-1);
    }
    rc = pthread_create(&myThread2, NULL, PrintChar, (void *)chp);
    if (rc) {
        perror("Failed in calling pthread_create");
        exit(-1);
    }

    pthread_exit(NULL);
}