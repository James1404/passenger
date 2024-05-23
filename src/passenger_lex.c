#include "passenger_lex.h"

#include "stdlib.h"

//
// --- Token Array ---
//
TokenArray TokenArray_make() {
    TokenArray r = {
        .data = NULL,
        .allocated = 0,
        .len = 0
    };

    return r;
}

void TokenArray_free(TokenArray* array) {
    if(array->data) free(array->data);
    array->data = NULL;
}

void TokenArray_push(TokenArray* array, Token elem) {
    if(array->allocated == 0 || !array->data) {
        array->allocated = 8;
        array->data = malloc(sizeof(Token)*array->allocated);
    }

    array->data[array->len] = elem;
    array->len++;

    if(array->len >= array->allocated) {
        array->allocated *= 2;
        array->data = realloc(array->data, sizeof(Token)*array->allocated);
    }
}

Token TokenArray_at(TokenArray* array, i32 idx) {
    return array->data[idx];
}

//
// --- Lexer ---
//
Lexer Lexer_make(String input) {
    Lexer lexer = {};
    lexer.input = input;
    lexer.tokens = TokenArray_make();
    lexer.position = 0;
    return lexer;
}

void Lexer_free(Lexer* lexer) {
    TokenArray_free(&lexer->tokens);
}

char Lexer_peek(Lexer* lexer) {
    i32 p = lexer->position + 1;
    if(p < lexer->input.length) {
        return String_index(lexer->input, p);
    }

    return NULL;
}

char Lexer_current(Lexer* lexer) {
    return String_index(lexer->input, lexer->position);
}

void Lexer_advance(Lexer* lexer) {
    lexer->position++;
}

void Token_make(Lexer* lexer, TokenType type) {
    Token t = {};

    t.text = String_substr(lexer->input, lexer->start, lexer->position - lexer->start);
    t.line = lexer->line;
    t.loc = lexer->position;
    t.type = type;

    TokenArray_push(&lexer->tokens, t);
}

static bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static bool isNumber(char c) {
    return c >= '0' && c <= '9';
}

static bool isWhitespace(char c) {
    switch(c) {
            return true;
        default:
            return false;
    }
}

void Lexer_run(Lexer* lexer) {
    while(lexer->position < lexer->input.length) {
        char c = Lexer_current(lexer);
        lexer->start = lexer->position;

        Lexer_advance(lexer);

        switch(c) {
        case '+': Token_make(lexer, TOKEN_PLUS); break;
        case '-': Token_make(lexer, TOKEN_MINUS); break;
        case '/': Token_make(lexer, TOKEN_DIVIDE); break;
        case '*': Token_make(lexer, TOKEN_MULTIPLY); break;

        case ':': Token_make(lexer, TOKEN_COLON); break;
        case ';': Token_make(lexer, TOKEN_SEMICOLON); break;

        case '.': Token_make(lexer, TOKEN_DOT); break;
        case ',': Token_make(lexer, TOKEN_COMMA); break;

        case '"':
            lexer->start = lexer->position;
            while(Lexer_peek(lexer) != '"') Lexer_advance(lexer);
            Token_make(lexer, TOKEN_STRING);
            Lexer_advance(lexer);
            break;
        
        case '\n':
            lexer->line++;
        case ' ':
        case '\t':
        case '\r':
            break;

        default:
            if(isLetter(c)) {
                while(isLetter(Lexer_current(lexer)) || Lexer_current(lexer) == '_')
                {
                    Lexer_advance(lexer);
                }

                Token_make(lexer, TOKEN_IDENTIFIER);
                continue;
            }

            if(isNumber(c)) {
                while(isNumber(Lexer_current(lexer)) || Lexer_current(lexer) == '.')
                {
                    Lexer_advance(lexer);
                }

                Token_make(lexer, TOKEN_NUMBER);
                continue;
            }

            break;
        }
    }

    Token_make(lexer, TOKEN_EOF);
}

static void consume_identifier(Lexer* lexer, char expected, String error) {
    int start = lexer->position;
    if(isLetter(Lexer_current(lexer))) {
        while(isLetter(Lexer_current(lexer)) || isNumber(Lexer_current(lexer))) Lexer_advance(lexer);

        String id = String_substr(lexer->input, start, lexer->position);

        return;
    }
}
