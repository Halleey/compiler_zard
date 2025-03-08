#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>');
}

int is_delimeter(char c) {
    return (c == ';' || c== ',' || c == '(' || c == ')' || c == '{' || c == '}');
}

//fução para caso seja keyword

// Função para verificar se é uma palavra-chave
int is_keyword(const char *value) {
    return (strcmp(value, "if") == 0 || strcmp(value, "else") == 0 || strcmp(value, "while") == 0 ||
            strcmp(value, "int") == 0 || strcmp(value, "boolean") == 0 || strcmp(value, "main") == 0);
}

