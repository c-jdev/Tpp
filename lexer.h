#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "types.h"

typedef struct {
    int start;
    int current;
    int line; 
    long file_size;
    char *buffer;
    bool hadError;
} Lexer;

char *read_entire_file(const char *filename, long *out_size);

bool at_end(Lexer *lexer);

bool match_next(Lexer *lexer, char expected);

Lexer *make_lexer(void);

Token *scan_token(Lexer *lexer, Token_List *token_list);

Token_List *scan_tokens(void);

#endif