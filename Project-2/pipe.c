#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define INPUT 0
#define OUTPUT 1

int main(void){
    int result;
    int read_count;
    int subp1[2], subp2[2];
    char buffer[255];
    char *message1 = "Child 1 is sending a message!";
    char *message2 = "Child 2 is sending a message!";
    result = pipe(subp1);
    if(result < 0 ){
        perror("Failed in calling pipe");
        exit(1);
    }
    result = fork();
    if(result < 0){
        perror("Failed in calling fork");
        exit(1);
    }
    else if(result != 0){
        result = pipe(subp2);
        if(result < 0 ){
            perror("Failed in calling pipe");
            exit(1);
        }
        result = fork();
        if(result < 0){
            perror("Failed in calling fork");
            exit(1);
        }
        else if(result == 0){
            result = write(subp2[OUTPUT], message2, strlen(message2));
            if(result <0){
                perror("In child 1, failed to sending message");
                exit(1);
            }
        }
        else{
            read_count = read(subp1[INPUT], buffer, sizeof(buffer));
            if(read_count < 0){
                perror("In Parent, failed to receive message from child1");
                exit(1);
            }
            else{
                buffer[read_count] = '\0';
                printf("%d bytes of data received from child1: %s\n", read_count, buffer);
            }
            read_count = read(subp2[INPUT], buffer, sizeof(buffer));
            if(read_count < 0){
                perror("In Parent, failed to receive message from child2");
                exit(1);
            }
            else{
                buffer[read_count] = '\0';
                printf("%d bytes of data received from child2: %s\n", read_count, buffer);
            }
        }
    }
    else{
        result = write(subp1[OUTPUT], message1, strlen(message1));
        if(result <0){
            perror("In child 1, failed to sending message");
            exit(1);
        }
    }
    return 0;
}