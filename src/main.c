#include <stdio.h>
#include <string.h>

#define BUFFER_LENGTH 100
#define PROMPT "ok\n>"


int main(void){
    char buffer[BUFFER_LENGTH];
    char c;
    int length = 0;
    int cmp_result = 0;

    printf(PROMPT);
    do{
        c = fgetc(stdin);

        if(length < BUFFER_LENGTH && c != '\n'){
            buffer[length] = c;
        } else {
            buffer[BUFFER_LENGTH - 1] = '\0';
        }

        if(c == '\n') {
            buffer[length] = '\0';
            cmp_result = strncmp(buffer, "exit", BUFFER_LENGTH);

            if(cmp_result == 0){
                break;
            }

            printf(PROMPT);
            length = -1;
        }

        length++;
    } while(c != 27);

    printf("Hello World!!: %s\n", buffer);
    return 0;
}