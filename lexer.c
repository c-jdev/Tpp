#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"
#include "token_list.h"

char *read_entire_file(const char *filename, long *out_size) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("error opening source file");
        return NULL;
    }

    if (fseek(file, 0L, SEEK_END) != 0) {
        perror("error seeking source file");
        fclose(file);
        return NULL;
    }

    long file_size = ftell(file);
    if (file_size < 0) {
        perror("error telling source file");
        fclose(file);
        return NULL;
    }

    rewind(file);

    char *buffer = (char*) malloc(file_size + 1);
    if (buffer == NULL) {
        perror("error allocating source buffer");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read < (size_t)file_size) {
        perror("error reading source file");
        fclose(file);
        free(buffer);
        return NULL;
    }

    buffer[bytes_read] = '\0';
    fclose(file);

    *out_size = (long)bytes_read;
    return buffer;
}

Lexer *make_lexer(void) {      
    Lexer *lexer = (Lexer*) malloc(sizeof(Lexer));
    if (lexer == NULL) {
        perror("error allocating lexer");
        return NULL;
    }   

    long *file_size;
    lexer->buffer = read_entire_file("test.ctl", file_size);
    lexer->start = 0;
    lexer->current = 0;
    lexer->line = 1;
    lexer->file_size = *file_size;

    return lexer;
}

Token *scan_token(Lexer *lexer) {
    char current_char = lexer->buffer[lexer->current];
    lexer->current++;
    
    switch(current_char) {
        // Single
        case()
    }
}

Token_List *scan_tokens(void) {
    Token_List *token_list = make_token_list(64);
    Lexer *lexer = scan_source();

    while (lexer->current != lexer->file_size) {
        lexer->start = lexer->current;
        scanToken();
    }

    return token_list;
}