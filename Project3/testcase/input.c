#include <stdio.h>

int main(void){
    char buffer[255];
    while(fgets(buffer, 255, stdin))
        printf("%s\n", buffer);
}