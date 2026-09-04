#include <stdlib.h>
#include <stdio.h>

#include "token.h"

Token_List *make_token_list(int size) {
    Token_List *list = (Token_List*) malloc(sizeof(Token_List));
    if (list == NULL) {
        perror("error allocating token list");
        return NULL;
    }

    list->tokens = calloc(size, sizeof(Token));
    if (list->tokens == NULL) {
        perror("error allocating token list buffer");
        return NULL;
    }
    list->capacity = size;
    list->count = 0; 

    return list;
}

void insert_token(Token_List *list, Token token) {
    if (list->count == list->capacity) {
        list->tokens = realloc(list->tokens, (sizeof(Token)) * (list->capacity*2));
        if (list->tokens == NULL) {
            perror("error rallocating token list buffer");
            return;
        }

        list->capacity *= 2;
        list->tokens[list->count] = token;
        list->count++;
        return;
    } 
    list->tokens[list->count] = token;
    list->count++;
}

void print_token_list(Token_List *list) {
    printf("Token Capacity: %d, Token Count: %d\n", list->capacity, list->count);

    if (list->count == 0) { 
        printf("Token list is empty\n");
        return;
    }
    
    for (int i = 0; i < list->count; i++) {
        Token token = list->tokens[i];
        printf("Token Type: %s, Lexeme: %.*s, Line Number: %d\n", 
            get_token_type_string(token), token.length, token.lexeme, token.line);
    }
}

const char *get_token_type_string(Token token) {
    switch (token.type) {
        // Special Tokens
        case _EOF:          return "EOF";

        // Single-Character Tokens
        case LEFT_PAREN:    return "LEFT_PAREN";
        case RIGHT_PAREN:   return "RIGHT_PAREN";
        case LEFT_BRACE:    return "LEFT_BRACE";
        case RIGHT_BRACE:   return "RIGHT_BRACE";
        case COMMA:         return "COMMA";
        case DOT:           return "DOT";
        case PLUS:          return "PLUS";
        case MINUS:         return "MINUS";
        case SEMICOLON:     return "SEMICOLON";
        case SLASH:         return "SLASH";
        case STAR:          return "STAR";
        case EQUAL:         return "EQUAL";
        case GREATER:       return "GREATER";
        case LESSER:        return "LESSER";
        case BACKSLASH:     return "BACKSLASH";
        case NOT:           return "NOT";

        // Multi-Character Tokens
        case GREATER_EQUAL: return "GREATER_EQUAL";
        case LESSER_EQUAL:  return "LESSER_EQUAL";
        case NOT_EQUAL:     return "NOT_EQUAL";
        case EQUAL_EQUAL:   return "EQUAL_EQUAL";

        // Literals
        case L_STRING:      return "L_STRING";
        case L_NUMBER:      return "L_NUMBER";

        // Keywords
        case AND:           return "AND";
        case OR:            return "OR";
        case IF:            return "IF";
        case ELSE:          return "ELSE";
        case WHILE:         return "WHILE";
        case FOR:           return "FOR";
        case CLASS:         return "CLASS";
        case FUNC:          return "FUNC";
        case NIL:           return "NIL";
        case RETURN:        return "RETURN";
        case TRUE:          return "TRUE";
        case FALSE:         return "FALSE";
        case THIS:          return "THIS";
        case PRINT:         return "PRINT";

        // Types
        case VAR:           return "VAR";
        case STRING:        return "STRING";
        case CHAR:          return "CHAR";
        case INT:           return "INT";
        case FLOAT:         return "FLOAT";

        // Fallback for safety
        default:            return "UNKNOWN_TOKEN";
    }
}