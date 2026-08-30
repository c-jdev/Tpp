#ifndef TYPES_H
#define TYPES_H

typedef enum {
    // Character Tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, PLUS, MINUS, SEMICOLON, SLASH, STAR,
    EQUAL, GREATER, LESS, 

    // Multi-Character Tokens
    GREATER_EQUAL, LESSER_EQUAL, NOT_EQUAL, EQUAL_EQUAL,

    // Literals
    STRING, NUMBER,

    // Keywords
    AND, OR, IF, ELSE, WHILE, FOR, CLASS, FUNC, NIL, RETURN,
    TRUE, FALSE, THIS, PRINT, 

    // Types
    VAR, 

    // Special Tokens
    _EOF = -1
} Token_Type;

typedef struct {
    Token_Type type;
    char lexeme[64];
    int line;
} Token;

typedef struct {
    Token *tokens;
    size_t count;
    size_t capacity;
} Token_List;

#endif