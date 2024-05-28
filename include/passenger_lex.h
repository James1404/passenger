#ifndef PASSENGER_LEX_H
#define PASSENGER_LEX_H

#include "passenger_common.h"
#include "passenger_hash.h"

#define FOR_TOKENS(DO)\
    DO(TOKEN_NONE)\
\
    DO(TOKEN_NUMBER) DO(TOKEN_STRING) DO(TOKEN_IDENTIFIER)\
\
    DO(TOKEN_VAR) DO(TOKEN_CONST)\
\
    DO(TOKEN_TRUE) DO(TOKEN_FALSE)\
\
    DO(TOKEN_FN) DO(TOKEN_RETURN)\
    DO(TOKEN_IF) DO(TOKEN_ELSE)\
    DO(TOKEN_CONTINUE) DO(TOKEN_BREAK)\
    DO(TOKEN_FOR) DO(TOKEN_WHILE)\
\
    DO(TOKEN_LPAREN) DO(TOKEN_RPAREN)\
    DO(TOKEN_LBRACE) DO(TOKEN_RBRACE)\
    DO(TOKEN_LBRACKET) DO(TOKEN_RBRACKET)\
    DO(TOKEN_SEMICOLON) DO(TOKEN_COLON)\
    DO(TOKEN_DOT) DO(TOKEN_COMMA)\
\
    DO(TOKEN_PLUS) DO(TOKEN_MINUS) DO(TOKEN_MULTIPLY) DO(TOKEN_DIVIDE)\
    DO(TOKEN_PLUSEQUAL) DO(TOKEN_MINUSEQUAL) DO(TOKEN_MULTIPLYEQUAL) DO(TOKEN_DIVIDEEQUAL)\
\
    DO(TOKEN_EQUAL) DO(TOKEN_NOT)\
    DO(TOKEN_LESS) DO(TOKEN_GREATER)\
    DO(TOKEN_EQUALEQUAL) DO(TOKEN_NOTEQUAL)\
    DO(TOKEN_LESSEQUAL) DO(TOKEN_GREATEREQUAL)\



typedef enum {
#define DEFINE_ENUM(x) x,
    FOR_TOKENS(DEFINE_ENUM)
#undef DEFINE_ENUM
} TokenType;

String TokenType_tostring(TokenType type);

typedef struct {
    TokenType type;
    u64  line, loc;
    String text;
} Token;

typedef struct {
    Token* data;
    u64 allocated, len;
} TokenArray;

TokenArray TokenArray_make();
void TokenArray_free(TokenArray* array);

void TokenArray_push(TokenArray* array, Token elem);
Token TokenArray_at(TokenArray* array, u64 idx);

typedef struct {
    String input;
    TokenArray tokens;

    u64 line, start, position;
} Lexer;

Lexer Lexer_make(String input);
void Lexer_free(Lexer* lexer);
char Lexer_peek(Lexer* lexer);
char Lexer_current(Lexer* lexer);
void Lexer_advance(Lexer* lexer);
void Lexer_run(Lexer* lexer);

void Token_make(Lexer* lexer, TokenType type);

#endif//PASSENGER_LEX_H
