#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void int_handler();

int main(int argc, char ** argv)
{
    int sig;
    sigset( SIGINT, int_handler );
    sig = fork();
    if(sig < 0){
        perror("Failed to create subprocess");
        return EXIT_FAILURE;
    }
    else if(sig == 0){
        printf("The child ID is %d\n", getpid());
        while(1)
            ;
    }
    else{
        printf("The parent ID is %d\n", getpid());
        while(1)
            ;
    }
    return EXIT_SUCCESS;
}

void int_handler()
{
    printf("Get a SIGINT signal!\nThe process ID is %d\n", getpid());
}