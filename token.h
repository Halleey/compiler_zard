#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    KEYWORD, IDENTIFIER, OPERATOR, NUMBER, STRING, DELIMITER, END_EOF, BOOLEAN, INSTANCE, METHODS
} TokenType;

typedef struct {
    TokenType type;
    char *value; 
} Token;

// Declaração das funções do lexer
Token create_token(TokenType type, const char *value);
Token get_next_token(const char **src);
void free_token(Token *token);

#endif // TOKEN_H
