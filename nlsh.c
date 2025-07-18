#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

int main(int argc, char *argv[]){
    
    char input[MAX_INPUT];
    char *tokens;
    char *args[MAX_ARGS];
    
    while(1){
        printf("nlsh> ");
        fflush(stdout);
        
        if(fgets(input, MAX_INPUT, stdin) == NULL) {
            break; 
        }
        
        input[strcspn(input, "\n")] = 0;

        char translated[MAX_INPUT];
        FILE *pipe;
        char cmd[MAX_INPUT];

        snprintf(cmd, sizeof(cmd), "python3 nlp_translate.py \"%s\"", input);
        pipe = popen(cmd, "r");

        if (pipe == NULL) {
            perror("popen failed");
            continue;
        }

        if (fgets(translated, MAX_INPUT, pipe) != NULL) {
            translated[strcspn(translated, "\n")] = 0;
            strncpy(input, translated, MAX_INPUT);
        }

        pclose(pipe);
        
        if(strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            break;
        }
        
        int i = 0;
        tokens = strtok(input, " ");
        while (tokens != NULL && i < MAX_ARGS - 1) {
            args[i++] = tokens;
            tokens = strtok(NULL, " ");
        }
        args[i] = NULL; 
        
        if (args[0] == NULL) {
            continue;
        }
        
        // for (int j = 0; j < i; j++) {
        //     printf("arg[%d]: %s\n", j, args[j]);
        // }

        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL || chdir(args[1]) != 0) {
                perror("cd failed");
        }
        continue;
    }

        pid_t pid = fork();

        if (pid == -1) {
            fprintf(stderr, "Call to fork failed... aborting.\n");
            exit(1);
        }

        else if(pid == 0){
           execvp(args[0], args);
           perror("exec failed");
           exit(1);
        }

        else{
            waitpid(pid, NULL, 0);
        }

    }
    
    return 0;
}