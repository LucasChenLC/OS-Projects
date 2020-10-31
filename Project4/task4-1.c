#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *PrintHello(void) {
    printf("Hello Multi-Thread! It's me, thread #%ld!\n", (long)pthread_self());
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t myThread1, myThread2;
    int rc;
    rc = pthread_create(&myThread1, NULL, PrintHello, NULL);
    if (rc) {
        perror("Failed in calling pthread_create");
        exit(-1);
    }
    rc = pthread_create(&myThread2, NULL, PrintHello, NULL);
    if (rc) {
        perror("Failed in calling pthread_create");
        exit(-1);
    }

    pthread_exit(NULL);
}