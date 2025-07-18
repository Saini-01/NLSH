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

        //clears buffer
        fflush(stdout);
        
        //if input is null, break out of loop
        if(fgets(input, MAX_INPUT, stdin) == NULL) {
            break; 
        }
        
        //format input to be without new line
        input[strcspn(input, "\n")] = 0;

        //create translated, file, and cmd buffer
        char translated[MAX_INPUT];
        FILE *pipe;
        char cmd[MAX_INPUT];

        //format's string and writes it into cmd buffer, reads output from python file
        snprintf(cmd, sizeof(cmd), "python nlp_translate.py \"%s\"", input);
        pipe = popen(cmd, "r");

        //if pipe fails to open 
        if (pipe == NULL) {
            perror("popen failed");
            continue;
        }

        //if sucessfully read from pipe, format and replace input with translated command
        if (fgets(translated, MAX_INPUT, pipe) != NULL) {
            translated[strcspn(translated, "\n")] = 0;
            strncpy(input, translated, MAX_INPUT);
        }

        //close the pipe
        pclose(pipe);
        
        //exit on "exit" or "quit"
        if(strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            break;
        }
        
        // tokenize the input string into arguments for execvp
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

        //cd implementation using chdir func
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL || chdir(args[1]) != 0) {
                perror("cd failed");
        }
        continue;
    }

        //creates child and parent processes 
        pid_t pid = fork();


        if (pid == -1) {
            fprintf(stderr, "Call to fork failed... aborting.\n");
            exit(1);
        }

        //execute on child process
        else if(pid == 0){
           execvp(args[0], args);
           perror("exec failed");
           exit(1);
        }

        //parent process waits for child process
        else{
            waitpid(pid, NULL, 0);
        }

    }
    
    return 0;
}