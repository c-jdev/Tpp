#include <stdio.h>

#include "lexer.h"
#include "token.h"

int main() {
    Token_List *list = scan_tokens();

    print_token_list(list);

    return 0;
}