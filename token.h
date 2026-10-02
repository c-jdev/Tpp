#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

typedef enum {
    // Single-Character Tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, PLUS, MINUS, SEMICOLON, SLASH, STAR,
    EQUAL, GREATER, LESSER, BACKSLASH, NOT,

    // Multi-Character Tokens
    GREATER_EQUAL, LESSER_EQUAL, NOT_EQUAL, EQUAL_EQUAL,

    // Literals
    LITERAL_STRING, LITERAL_INT, LITERAL_FLOAT,

    // Keywords
    AND, OR, IF, ELSE, WHILE, FOR, FUNC, NIL, RETURN,
    TRUE, FALSE, PRINT, 

    // Types
    VAR, STRING, CHAR, INT, FLOAT,

    IDENTIFIER,

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

Token_List *make_token_list(int size);
void insert_token(Token_List *token_list, Token token);
void print_token_list(Token_List *token_list);
const char *get_token_type_string(Token token);

#endif