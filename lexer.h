#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include "types.h"

typedef struct {
    int start;
    int current;
    int line; 
    long file_size;
    char *buffer
} Lexer;

char *read_entire_file(const char *filename, long *out_size);
Lexer *make_lexer(void);
Token *scan_token(char buffer[]);
Token_List *scan_tokens(void);

#endif