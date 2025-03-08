#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>');
}

int is_delimeter(char c) {
    return (c == ';' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}');
}

// Função para verificar se é uma palavra-chave
int is_keyword(const char *value) {
    return (strcmp(value, "if") == 0 || strcmp(value, "else") == 0 || strcmp(value, "while") == 0 ||
            strcmp(value, "int") == 0 || strcmp(value, "boolean") == 0 || strcmp(value, "main") == 0);
}

// Função para verificar se é um identificador válido
int is_identifier(const char *value) {
    if (!isalpha(value[0])) {
        return 0;
    }
    for (int i = 1; value[i] != '\0'; i++) {
        if (!isalnum(value[i])) {
            return 0;
        }
    }
    return 1;
}

// Função para criar um token
Token create_token(TokenType type, const char *value) {
    Token token;
    token.type = type;
    token.value = strdup(value);  
    return token;
}

// Libera memória
void free_token(Token * token) {
    if (token->value != NULL) {
        free(token->value);
        token->value = NULL;
    }
}


Token get_next_token(const char **src) {
    while (**src != '\0') {
        if (isspace(**src)) {
            (*src)++;
            continue;
        }

        if (is_operator(**src)) {
            char op[2] = {**src, '\0'};
            (*src)++;
            printf("Token gerado: OPERATOR [%s]\n", op);  // 🚨 Depuração
            return create_token(OPERATOR, op);
        }

        if (is_delimeter(**src)) {  
            char delimiter[2] = {**src, '\0'};
            (*src)++;
            printf("Token gerado: DELIMITER [%s]\n", delimiter);  // 🚨 Depuração
            return create_token(DELIMITER, delimiter);
        }

        if (isdigit(**src)) {
            const char *start = *src;
            while (isdigit(**src)) {
                (*src)++;
            }
            size_t len = *src - start;
            char *num = (char *)malloc(len + 1);
            strncpy(num, start, len);
            num[len] = '\0';
            printf("Token gerado: NUMBER [%s]\n", num);  // 🚨 Depuração
            Token token = create_token(NUMBER, num);
            free(num);  
            return token;
        }

        if (isalpha(**src)) {
            const char *start = *src;
            while (isalnum(**src)) {
                (*src)++;
            }
            size_t len = *src - start;
            char *id = (char *)malloc(len + 1);
            strncpy(id, start, len);
            id[len] = '\0';

            if (is_keyword(id)) {
                printf("Token gerado: KEYWORD [%s]\n", id);  // 🚨 Depuração
                Token token = create_token(KEYWORD, id);
                free(id);
                return token;
            } else if (is_identifier(id)) {
                printf("Token gerado: IDENTIFIER [%s]\n", id);  // 🚨 Depuração
                Token token = create_token(IDENTIFIER, id);
                free(id);
                return token;
            }
        }

        if (**src == '"') {
            (*src)++;
            const char *start = *src;
            while (**src != '"' && **src != '\0') {
                (*src)++;
            }
            size_t len = *src - start;
            char *str = (char *)malloc(len + 1);
            strncpy(str, start, len);
            str[len] = '\0';

            if (**src == '"') (*src)++;
            printf("Token gerado: STRING [%s]\n", str);  // 🚨 Depuração
            Token token = create_token(STRING, str);
            free(str); 
            return token;
        }

        if (**src == '\0') {
            printf("Token gerado: END_EOF\n");  // 🚨 Depuração
            return create_token(END_EOF, "EOF");
        }

        (*src)++;
    }
    return create_token(END_EOF, "EOF");
}

int main() {
  
    const char *src = "int main() { int x = 10; if (x > 5) { x = 3; } }";
    
    const char *ptr = src;
    Token token;


    while ((token = get_next_token(&ptr)).type != END_EOF) {
        printf("Tipo: %d, Valor: %s\n", token.type, token.value);
        free_token(&token);  
    }

    return 0;
}
