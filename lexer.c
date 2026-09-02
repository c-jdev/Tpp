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

char get_substring(Lexer *lexer) {
    char substring[64];
    for (int i = 0; i < (lexer->current - lexer->start); i++) {
        substring[i] = lexer->buffer[lexer->start + i];
    }

    return substring;
}

char peek_next(Lexer *lexer) {
    if (at_end(lexer)) {
        return '\0';
    }
    return lexer->buffer[lexer->current];
}

char advance(Lexer *lexer) {
    char current_char = lexer->buffer[lexer->current];
    lexer->current++;

    return current_char;
}

bool at_end(Lexer *lexer) {
    if (lexer->current == lexer->file_size) {
        return true;
    }
    return false;
}

bool match_next(Lexer *lexer, char expected) {
    if (at_end(lexer)) {
        return false;
    }
    if (lexer->buffer[lexer->current] != expected) {
        return false;
    }

    lexer->current++;
    return true;
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
    lexer->hadError = false;

    return lexer;
}

Token *scan_token(Lexer *lexer, Token_List *token_list) {
    char current_char = advance(lexer);
    
    switch(current_char) {
        // Single-character Tokens
        case('('):
            insert_token(token_list, 
                (Token){ 
                    .type = LEFT_PAREN, 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case(')'):
            insert_token(token_list, 
                (Token){ 
                    .type = RIGHT_PAREN, 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case('{'):
            insert_token(token_list, 
                (Token){ 
                    .type = LEFT_BRACE, 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case('}'):
            insert_token(token_list, 
                (Token){ 
                    .type = RIGHT_BRACE, 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case(','):
            insert_token(token_list, 
                (Token){ 
                    .type = COMMA, 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case('.'):
            insert_token(token_list, 
                (Token){ 
                    .type = DOT, 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case('+'):
            insert_token(token_list, 
                (Token){ 
                    .type = PLUS, 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case('-'):
            insert_token(token_list, 
                (Token){ 
                    .type = MINUS, 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case(';'):
            insert_token(token_list, 
                (Token){ 
                    .type = SEMICOLON, 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case('\\'):
            insert_token(token_list, 
                (Token){ 
                    .type = BACKSLASH, 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case('*'):
            insert_token(token_list, 
                (Token){ 
                    .type = STAR, 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case('='):
            insert_token(token_list, 
                (Token){ 
                    .type = (match_next(lexer, '=') ? EQUAL_EQUAL : EQUAL), 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case('>'):
            insert_token(token_list, 
                (Token){ 
                    .type = (match_next(lexer, '=') ? GREATER_EQUAL : GREATER), 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case('<'):
            insert_token(token_list, 
                (Token){ 
                    .type = (match_next(lexer, '=') ? LESSER_EQUAL : LESSER), 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case('!'):
            insert_token(token_list, 
                (Token){ 
                    .type = (match_next(lexer, '=') ? NOT_EQUAL : NOT), 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        case('/'):
            if (match_next(lexer, '/')) {
                while (peek_next(lexer) != '\n' && !at_end(lexer)) {
                    
                }
            }
            insert_token(token_list, 
                (Token){ 
                    .type = '/', 
                    .lexeme = get_substring(lexer), 
                    .line = lexer->line});
            break;
        default: 
            perror("error reading tokens");
            lexer->hadError = true;
            break;
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