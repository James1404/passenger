#include "passenger_lex.h"

#include "stdlib.h"

//
// --- TokenType ---
//

String TokenType_tostring(TokenType type) {
    switch(type) {
#define DEFINE_TOSTRING(x) case x: return String_make(#x);
        FOR_TOKENS(DEFINE_TOSTRING)
#undef DEFINE_TOSTRING
    }
}

//
// --- Token Array ---
//
TokenArray TokenArray_make() {
    return (TokenArray) {
        .data = NULL,
        .allocated = 0,
	.len = 0
    };
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

typedef struct LLNode {
    void* data;
    usize datasize;
    struct LLNode* next;
} LLNode;

Token TokenArray_at(TokenArray* array, u64 idx) {
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

bool Lexer_eof(Lexer* lexer) {
    return lexer->position >= lexer->input.length;
}

char Lexer_peek(Lexer* lexer) {
    if(Lexer_eof(lexer)) {
        return '\0';
    }

    return String_index(lexer->input, lexer->position + 1);
}

char Lexer_current(Lexer* lexer) {
    return String_index(lexer->input, lexer->position);
}

void Lexer_advance(Lexer* lexer) {
    lexer->position++;
}

void Token_make_identifier(Lexer* lexer) {
    Token t = {};

    t.text = String_substr(lexer->input, lexer->start, lexer->position - lexer->start);
    t.line = lexer->line;
    t.loc = lexer->position;
    t.type = Passenger_GetKeyword(t);

    TokenArray_push(&lexer->tokens, t);
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

static void Token_match(Lexer* lexer, char match, TokenType t, TokenType f) {
    if(Lexer_current(lexer) == match) {
        Lexer_advance(lexer);
        Token_make(lexer, t);
    }
    else {
        Token_make(lexer, f);
    }
}

void Lexer_run(Lexer* lexer) {
    while(lexer->position < lexer->input.length) {
        char c = Lexer_current(lexer);
        lexer->start = lexer->position;

        Lexer_advance(lexer);

        switch(c) {
        case '+': Token_match(lexer, '=', TOKEN_PLUSEQUAL, TOKEN_PLUS); break;
        case '-': Token_match(lexer, '=', TOKEN_MINUSEQUAL, TOKEN_MINUS); break;
        case '/': Token_match(lexer, '=', TOKEN_DIVIDEEQUAL, TOKEN_DIVIDE); break;
        case '*': Token_match(lexer, '=', TOKEN_MULTIPLYEQUAL, TOKEN_MULTIPLY); break;

        case '<': Token_match(lexer, '=', TOKEN_LESSEQUAL, TOKEN_LESS); break;
        case '>': Token_match(lexer, '=', TOKEN_GREATEREQUAL, TOKEN_GREATER); break;

        case '!': Token_match(lexer, '=', TOKEN_NOTEQUAL, TOKEN_NOT); break;

        case '=': Token_match(lexer, '=', TOKEN_EQUALEQUAL, TOKEN_EQUAL); break;

        case ':': Token_make(lexer, TOKEN_COLON); break;
        case ';': Token_make(lexer, TOKEN_SEMICOLON); break;

        case '.': Token_make(lexer, TOKEN_DOT); break;
        case ',': Token_make(lexer, TOKEN_COMMA); break;

        case '(': Token_make(lexer, TOKEN_LPAREN); break;
        case ')': Token_make(lexer, TOKEN_RPAREN); break;

        case '[': Token_make(lexer, TOKEN_LBRACKET); break;
        case ']': Token_make(lexer, TOKEN_RBRACKET); break;

        case '{': Token_make(lexer, TOKEN_LBRACE); break;
        case '}': Token_make(lexer, TOKEN_RBRACE); break;

        case '"':
            lexer->start = lexer->position;
            for(;;) {
                if(Lexer_eof(lexer)) break; // error message
                if(Lexer_current(lexer) == '"') break;
                Lexer_advance(lexer);
            }

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

                Token_make_identifier(lexer);
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
}
