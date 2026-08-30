#include <stdlib.h>

#include "token_list.h"

Token_List *make_token_list(int size) {
    Token_List *token_list = (Token_List*) malloc(sizeof(Token_List));
    if (token_list == NULL) {
        perror("error allocating token list");
        return NULL;
    }

    token_list->tokens = calloc(size, sizeof(Token));
    if (token_list->tokens == NULL) {
        perror("error allocating token list buffer");
        return NULL;
    }
    token_list->capacity = size;
    token_list->count = 0; 

    return token_list;
}

void insert_token(Token_List *token_list, Token token) {
    printf("Inserting -> Token Type: %d, Lexeme: %s, Line Number: %d\n", 
            token.type, token.lexeme, token.line);
    if (token_list->count == token_list->capacity) {
        token_list->tokens = realloc(token_list->tokens, (sizeof(Token)) * (token_list->capacity*2));
        if (token_list->tokens == NULL) {
            perror("error rallocating token list buffer");
            return NULL;
        }

        token_list->capacity *= 2;
        token_list->tokens[token_list->count] = token;
        token_list->count++;
        return;
    } 
    token_list->tokens[token_list->count] = token;
    token_list->count++;
}

void print_token_list(Token_List *token_list) {
    printf("Token Capacity: %d, Token Count: %d\n", token_list->capacity, token_list->count);

    if (token_list->count == 0) { 
        printf("Token list is empty\n");
        return;
    }
    
    for (int i = 0; i < token_list->count; i++) {
        Token token = token_list->tokens[i];
        printf("Token Type: %d, Lexeme: %s, Line Number: %d\n", token.type, token.lexeme, token.line);
    }
}