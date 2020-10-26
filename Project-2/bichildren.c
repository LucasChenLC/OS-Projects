#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    int result;
    printf("Original\n");
    result = fork();
    if(result < 0){
        perror("Failed in calling fork");
        exit(1);
    }
    else if(result == 0)
        printf("Child 1\n");
    else{
        printf("Parent\n");
        result = fork();
        if(result < 0){
            perror("Failed in calling fork");
            exit(1);
        }
        else if(result != 0)
            printf("Child 2\n");
    }
    return 0;
}