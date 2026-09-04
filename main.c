#include <stdio.h>

#include "lexer.h"
#include "token_list.h"
#include "types.h"

int main() {
    Token_List *list = scan_tokens();

    print_token_list(list);

    return 0;
}