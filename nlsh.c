#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024

int main(int argc, char *argv[]){
    char input[MAX_INPUT];
    
    while(1){
        printf("nlsh> ");
        fflush(stdout);
        
        if(fgets(input, MAX_INPUT, stdin) == NULL) {
            break; 
        }
        
        input[strcspn(input, "\n")] = 0;
        
        if(strcmp(input, "exit") == 0) {
            break;
        }
        
        printf("You typed: %s\n", input);
    }
    
    return 0;
}