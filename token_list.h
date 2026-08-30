#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include "types.h"

Token_List *make_token_list(int size);
void insert_token(Token_List *token_list, Token token);
void print_token_list(Token_List *token_list);

#endif