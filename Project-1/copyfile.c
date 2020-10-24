#include <stdio.h>

int main(int argc, char **argv){
    if(argc != 3){
        printf("\033[31mError: There are not sufficient arguments.");
        return 1;
    }
    else{
        char buffer[255];
        FILE *source = fopen(argv[1], "r");
        if (source == NULL){
            printf("\033[31Error: The source is empty.\n");
            return 2;
        }
        FILE *destination = fopen(argv[2], "w");
        if (destination == NULL){
            printf("\033[31Error: Creating copy file failed.\n");
            return 3;
        }
        while(fgets(buffer, 255, source))
            fprintf(destination, "%s", buffer);
        printf("Copying file success.");
    }
    return 0;
}