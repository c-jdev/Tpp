#include "lexer.h"

char *read_entire_file(const char *filename, long *out_size) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening source file");
        return NULL;
    }

    if (fseek(file, 0L, SEEK_END) != 0) {
        perror("Error seeking source file");
        fclose(file);
        return NULL;
    }

    long file_size = ftell(file);
    if (file_size < 0) {
        perror("Error telling source file");
        fclose(file);
        return NULL;
    }

    rewind(file);

    char *buffer = (char*) malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Memory allocation for source buffer failed");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read < (size_t)file_size) {
        perror("Error reading source file");
        fclose(file);
        free(buffer);
        return NULL;
    }

    buffer[bytes_read] = '\0';
    fclose(file);

    *out_size = (long)bytes_read;
    return buffer;
}

Token_Type scan_token(char buffer[]) {
    
}

int scan_source(void) {      
    
}