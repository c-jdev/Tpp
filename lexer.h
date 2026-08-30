#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include "types.h"

typedef struct {
    int start;
    int current;
    int line; 
    char *buffer
} Lexer;

char *read_entire_file(const char *filename, long *out_size);
Token_Type scan_token(char buffer[]);
int scan_source(void);

#endif