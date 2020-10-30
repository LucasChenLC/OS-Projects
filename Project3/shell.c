#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void){
    char command[255];
    while(1) {
        int result, length, mode = 0, arg_num = 0, t = 1;
        fgets(command, 255, stdin);
        if(strcmp(command, "quit\n") == 0)
            break;
        result = fork();
        if (result < 0) {
            perror("Failed to create child");
            exit(1);
        }
        else if (result == 0) {
            // Child
            length = (int) strlen(command) - 1;
            command[length] = '\0';
            for (int i = 0; i < length; i++) {
                if (command[i] == '<') {
                    mode = 1;
                    break;
                } else if (command[i] == '>') {
                    mode = 2;
                    break;
                }
            }
            for (int j = 0; j < length; j++) {
                if (command[j] == 32 || command[j] == 9) {
                    arg_num++;
                    command[j] = '\0';
                }
            }
            if (!mode) {
                char **coms = (char **) malloc((arg_num + 2) * sizeof(char *));
                coms[0] = " ";
                for (int j = 0; j < length; j++) {
                    if (command[j] == '\0') {
                        coms[t++] = &command[j + 1];
                    }
                }
                coms[arg_num + 1] = NULL;
                result = execvp(command, coms);
                if (result == -1) {
                    perror("In child process, failed to exec a program");
                    exit(1);
                }
            }
            else {
                FILE *pipe, *fp;
                char buffer[255], *file;
                int count = 0;
                for (int s = (int) strlen(command);; s++) {
                    if (command[s] != '\0') {
                        count++;
                        if (count == 2) {
                            file = &command[s];
                            break;
                        }
                    }
                }
                if (mode == 1) {
                    pipe = popen(command, "w");
                    fp = fopen(file, "r");
                    if (pipe == NULL || fp == NULL) {
                        perror("In child process, error in opening the pipe or file");
                        exit(1);
                    }
                    while (fgets(buffer, 255, fp))
                        fprintf(pipe, "%s", buffer);
                }
                else {
                    pipe = popen(command, "r");
                    fp = fopen(file, "w");
                    while (fgets(buffer, 255, pipe))
                        fprintf(fp, "%s", buffer);
                    if (pipe == NULL || fp == NULL) {
                        perror("In child process, error in opening the file or pipe");
                        exit(1);
                    }
                }
                pclose(pipe);
                fclose(fp);
            }
            return EXIT_SUCCESS;
        }
        else    //parent
            wait(NULL);
    }
    return EXIT_SUCCESS;
}