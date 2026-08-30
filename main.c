#include <stdio.h>

#include "lexer.h"
#include "token_list.h"
#include "types.h"

int main() {
    // scan();
    Token_List *tokens = make_token_list(2);

    Token t1 = {LEFT_BRACE, "{", 5};
    Token t2 = {RIGHT_BRACE, "}", 5};
    Token t3 = {PLUS, "+", 17};
    Token t4 = {STRING, "Hello, World!", 7};
    
    insert_token(tokens, t1);
    insert_token(tokens, t2);
    insert_token(tokens, t3);
    print_token_list(tokens);
    insert_token(tokens, t4);
    print_token_list(tokens);

    return 0;
}