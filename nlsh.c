#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        
        for (int j = 0; j < i; j++) {
            printf("arg[%d]: %s\n", j, args[j]);
        }

    }
    
    return 0;
}