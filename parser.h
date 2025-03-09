//definindo os  métodos para o parser


#ifndef PARSER_H
#define PARSER_H
#include "token.h"

typedef struct Parser
{
    const char *src;
    Token current_token;
};

void parse_program(Parser * parser);
void parse_function_header(Parser * parser);
void parse_block(Parser * parser);
void parse_statement(Parser* parser);
void parse_variable_declaration(Parser * parser);
void advance(Parser *parser);
void eat(Parser *parser, TokenType expected);


#endif