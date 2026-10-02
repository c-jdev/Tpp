#include <stdlib.h>

#include "dict.h"

void dict_insert(Dict *dict, int index, char *key, Token_Type value) {
    dict->entries[index].key = key;
    dict->entries[index].value = value;
}

bool check_dict() {
    
}

Dict *make_dict(int size) {
    return (Dict *) malloc(size * sizeof(Dict));
}

Dict *make_keywords() {
    Dict *k = make_dict(17);

    dict_insert(k, 0, "and", AND);
    dict_insert(k, 0, "or", OR);
    dict_insert(k, 0, "if", IF);
    dict_insert(k, 0, "else", ELSE);
    dict_insert(k, 0, "while", WHILE);
    dict_insert(k, 0, "for", FOR);
    dict_insert(k, 0, "func", FUNC);
    dict_insert(k, 0, "nil", NIL);
    dict_insert(k, 0, "return", RETURN);
    dict_insert(k, 0, "true", TRUE);
    dict_insert(k, 0, "false", FALSE);
    dict_insert(k, 0, "print", PRINT);
    dict_insert(k, 0, "var", VAR);
    dict_insert(k, 0, "string", STRING);
    dict_insert(k, 0, "char", CHAR);
    dict_insert(k, 0, "int", INT);
    dict_insert(k, 0, "float", FLOAT);

    return k;
}