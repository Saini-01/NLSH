#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024

char* tokenize(char *tokens, char string[MAX_INPUT]);

int main(int argc, char *argv[]){
    
    char input[MAX_INPUT];
    char *tokens;
    
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
        
        tokenize(tokens, input);

    }
    
    return 0;
}

char* tokenize(char *tokens, char string[MAX_INPUT]){

    tokens = strtok(string, " ");

    while(tokens != NULL){
        printf("%s\n", tokens);
        tokens = strtok(NULL, " ,-");
    }

    return tokens;

}