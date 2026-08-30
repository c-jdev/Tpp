#include <stdio.h>

#include "lexer.h"
#include "token_list.h"
#include "types.h"

int main() {
    // scan();
    Token_List *tokens = make_token_list(2);

    printf("Token cap: %d, Token count: %d\n\n", tokens->capacity, tokens->count);

    Token t1 = {LEFT_BRACE, "{", 5};
    Token t2 = {RIGHT_BRACE, "}", 5};
    
    insert_token(tokens, t1);
    insert_token(tokens, t2);
    print_token_list(tokens);

    return 0;
}