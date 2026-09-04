#include <stdio.h>

#include "lexer.h"
#include "token.h"

int main() {
    Lexer *lexer = make_lexer();
    Token_List *list = make_token_list(32);

    scan_tokens(lexer, list);

    print_token_list(list);

    return 0;
}