#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    int result;
    result = fork();
    if (result < 0) {
        perror("Failed to create child");
        exit(1);
    }
    else if (result == 0) {
        // Child 1
        printf("Child process's PID is %d. My parent's PID is %d.\n", getpid(), getppid());
        if(argc < 2) {
            perror("In child process, there are not sufficient arguments.");
            exit(1);
        }
        else {
            printf("Child process is about to execute \"%s\"\n\n", argv[1]);
            if (argc == 2)
                result = execvp(argv[1], NULL);
            else
                result = execvp(argv[1], &argv[2]);
            if (result == -1)
                perror("In child process, failed to exec a program");
            exit(1);
        }
    }
    else {
        //parent
        int status;
        printf("Parent process's PID is %d.\n", getpid());
        printf("Parent process is waiting ... \n");
        wait(&status);
        printf("In parent process, status = 0x%x, WEXITSTATUS(status) = %d (i.e. 0x%x)\n", status, WEXITSTATUS(status), WEXITSTATUS(status));
    }
    return (EXIT_SUCCESS);
}
