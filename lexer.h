#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "token.h"

typedef struct {
    char message[64];  
    int line;  
} Error;

typedef struct {
    int start;
    int current;
    int line; 
    long file_size;
    char *buffer;
    Error *errors;
    bool hadError;
} Lexer;

char *read_entire_file(const char *filename, long *out_size); 
char peek_next(Lexer *lexer);
char advance(Lexer *lexer);
bool at_end(Lexer *lexer);
bool match_next(Lexer *lexer, char expected);
Lexer *make_lexer(void);
void scan_token(Lexer *lexer, Token_List *token_list);
void scan_tokens(Lexer *lexer, Token_List *token_list);

#endif