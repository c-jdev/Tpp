#include "lexer.h"

Token_Type scan_token(char buffer[]) {
    
}

int scan_source(void) {
    FILE *file = fopen("test.ctl", "r"); 

    if (file == NULL) {
        perror("fopen");
        return 1;
    }   

    char buffer[256];
    int start = 0;
    int current = 0;
    int line = 1;       
    
    while (fgets(buffer, sizeof buffer, file) != NULL) {
        printf("%s", buffer);
        scan_token(buffer);
    }  

    fclose(file);     
    return 0;
}