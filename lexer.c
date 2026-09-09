#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"

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

int get_length(Lexer *lexer) {
    return (lexer->current - lexer->start);
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

bool is_digit(char c) {
    return (c >= '0' && c <= '9');
}

Lexer *make_lexer(void) {      
    Lexer *lexer = (Lexer*) malloc(sizeof(Lexer));
    if (lexer == NULL) {
        perror("error allocating lexer");
        return NULL;
    }   

    long *file_size = (long*) malloc(sizeof(long));
    lexer->buffer = read_entire_file("test.ctl", file_size);
    lexer->start = 0;
    lexer->current = 0;
    lexer->line = 1;
    lexer->file_size = *file_size;
    lexer->hadError = false;

    return lexer;
}

void string_literal(Lexer *lexer) {
    while (peek_next(lexer) != '"' && !at_end(lexer)) {
        if (peek_next(lexer) == '\n') {
            lexer->line++;
        }
        advance(lexer);
    }

    if (at_end(lexer)) {
        perror("Unterminated string");
        return;
    }

    advance(lexer);
}

void number_literal(Lexer *lexer) {

}

void scan_token(Lexer *lexer, Token_List *list) {
    char current_char = advance(lexer);
    
    switch(current_char) {
        #pragma region Finished Cases
        // Operators
        case '(':
            insert_token(list, (Token){ .type = LEFT_PAREN, .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case ')':
            insert_token(list, (Token){ .type = RIGHT_PAREN, .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case '{':
            insert_token(list, (Token){ .type = LEFT_BRACE, .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case '}':
            insert_token(list, (Token){ .type = RIGHT_BRACE, .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case ',':
            insert_token(list, (Token){ .type = COMMA, .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case '.' :
            insert_token(list, (Token){ .type = DOT, .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case '+':
            insert_token(list, (Token){ .type = PLUS, .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case '-':
            insert_token(list, (Token){ .type = MINUS, .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case ';':
            insert_token(list, (Token){ .type = SEMICOLON, .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case '\\':
            insert_token(list, (Token){ .type = BACKSLASH, .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case '*':
            insert_token(list, (Token){ .type = STAR, .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case '=':
            insert_token(list, (Token){ .type = (match_next(lexer, '=') ? EQUAL_EQUAL : EQUAL), .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case '>':
            insert_token(list, (Token){ .type = (match_next(lexer, '=') ? GREATER_EQUAL : GREATER), .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case '<':
            insert_token(list, (Token){ .type = (match_next(lexer, '=') ? LESSER_EQUAL : LESSER), .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case '!':
            insert_token(list, (Token){ .type = (match_next(lexer, '=') ? NOT_EQUAL : NOT), .lexeme = &lexer->buffer[lexer->start], .length = (lexer->current - lexer->start), .line = lexer->line});
            break;
        case '/':
            if (match_next(lexer, '/')) {
                while (peek_next(lexer) != '\n' && !at_end(lexer)) {
                    advance(lexer);
                }
            } else {
                insert_token(list, (Token){ .type = SLASH, .lexeme = &lexer->buffer[lexer->start], .length = get_length(lexer), .line = lexer->line});    
            }
            break;
        #pragma endregion

        // Literals
        case '"':
            string_literal(lexer);
            insert_token(list, (Token){ .type = L_STRING, .lexeme = &lexer->buffer[lexer->start + 1], .length = (get_length(lexer) - 2), .line = lexer->line});
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            number_literal(lexer);
            insert_token(list, (Token){ .type = L_NUMBER})


        // Special Characters
        case '\n': 
            lexer->line++;
        case ' ':
        case '\r':
        case '\t':
            break;
        default: 
            perror("error reading tokens");
            lexer->hadError = true;

            break;
    }
}

void scan_tokens(Lexer *lexer, Token_List *list) {
    while (lexer->current != lexer->file_size) {
        lexer->start = lexer->current;
        scan_token(lexer, list);
    }
}