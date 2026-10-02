#ifndef DICT_H
#define DICT_H

#include "token.h"

typedef struct {
    char *key;
    Token_Type value;
} Dict_Entry;

typedef struct {
    Dict_Entry* entries;
    int size;
} Dict;

void dict_insert(Dict *dict, int index, char *key, Token_Type value);
Dict *make_dict(int size);
Dict *make_keywords();

#endif