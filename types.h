#ifndef TYPES_H
#define TYPES_H

typedef enum {
    // Single-Character Tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, PLUS, MINUS, SEMICOLON, SLASH, STAR,
    EQUAL, GREATER, LESSER, BACKSLASH, NOT,

    // Multi-Character Tokens
    GREATER_EQUAL, LESSER_EQUAL, NOT_EQUAL, EQUAL_EQUAL,

    // Literals
    L_STRING, L_NUMBER,

    // Keywords
    AND, OR, IF, ELSE, WHILE, FOR, CLASS, FUNC, NIL, RETURN,
    TRUE, FALSE, THIS, PRINT, 

    // Types
    VAR, STRING, CHAR, INT, FLOAT,

    // Special Tokens
    _EOF = -1
} Token_Type;

typedef struct {
    Token_Type type;
    const char *lexeme;
    int length;
    int line;
} Token;

typedef struct {
    Token *tokens;
    size_t count;
    size_t capacity;
} Token_List;

#endif