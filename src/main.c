#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#if DETTECTED_OS == Windows_NT
@load "fork"
#endif

#define BUFFER_LENGTH 100
#define PROMPT "ok\n>"


int execute(char *command) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execlp("ls", "-all") == -1) {
            perror("lsh");
        }
        exit(-1);
    } else if (pid < 0) {
        // Error forking
        perror("lsh");
    } else {
        // Parent process
        // do {
        //     wpid = waitpid(pid, &status, WUNTRACED);
        // } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

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

            execute(buffer);

            printf(PROMPT);
            length = -1;
        }

        length++;
    } while(c != 27);

    printf("Hello World!!: %s\n", buffer);
    return 0;
}