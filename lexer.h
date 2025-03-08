#ifndef LEXER_H
#define LEXER_H


typedef enum {
    KEYWORD, IDENTIFIER, OPERATOR, NUMBER, STRING, DELIMITER, END_EOF, BOOLEAN, INSTANCE, METHODS

} TokenType;

typedef struct Lexer
{
    TokenType type;
    char *value;
};

Lexer create_token(TokenType type, const char * value);
Lexer get_next_token(const char **src);
void free_token(Lexer *lexer);

#endif