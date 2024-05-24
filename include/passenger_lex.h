#ifndef PASSENGER_LEX_H
#define PASSENGER_LEX_H

#include "passenger_common.h"

typedef enum {
    TOKEN_NONE,
    TOKEN_VAR, TOKEN_CONST,

    TOKEN_NUMBER, TOKEN_STRING, TOKEN_IDENTIFIER,

    TOKEN_TRUE, TOKEN_FALSE,

    TOKEN_FN, TOKEN_RETURN,
    TOKEN_IF, TOKEN_ELSE,
    TOKEN_CONTINUE, TOKEN_BREAK,
    TOKEN_FOR, TOKEN_WHILE,

    TOKEN_LPAREN, TOKEN_RPAREN,
    TOKEN_LBRACE, TOKEN_RBRACE,
    TOKEN_LBRACKET, TOKEN_RBRACKET,
    TOKEN_SEMICOLON, TOKEN_COLON,
    TOKEN_DOT, TOKEN_COMMA,

    TOKEN_PLUS, TOKEN_MINUS, TOKEN_MULTIPLY, TOKEN_DIVIDE,
} TokenType;

String TokenType_tostring(TokenType type);

typedef struct {
    TokenType type;
    i32 line, loc;
    String text;
} Token;

typedef struct {
    Token* data;
    i32 allocated, len;
} TokenArray;

TokenArray TokenArray_make();
void TokenArray_free(TokenArray* array);

void TokenArray_push(TokenArray* array, Token elem);
Token TokenArray_at(TokenArray* array, i32 idx);

typedef struct {
    String input;
    TokenArray tokens;

    i32 line, start, position;
} Lexer;

Lexer Lexer_make(String input);
void Lexer_free(Lexer* lexer);
char Lexer_peek(Lexer* lexer);
char Lexer_current(Lexer* lexer);
void Lexer_advance(Lexer* lexer);
void Lexer_run(Lexer* lexer);

void Token_make(Lexer* lexer, TokenType type);

#endif//PASSENGER_LEX_H
