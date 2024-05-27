#include "passenger_lex.h"

#include "stdlib.h"

//
// --- TokenType ---
//

String TokenType_tostring(TokenType type) {
    switch(type) {
    case TOKEN_NONE: return String_make("TOKEN_NONE");
    case TOKEN_VAR: return String_make("TOKEN_VAR");
    case TOKEN_CONST: return String_make("TOKEN_CONST");
	
    case TOKEN_NUMBER: return String_make("TOKEN_NUMBER");
    case TOKEN_STRING: return String_make("TOKEN_STRING");
    case TOKEN_IDENTIFIER: return String_make("TOKEN_IDENTIFIER");
	
    case TOKEN_TRUE: return String_make("TOKEN_TRUE");
    case TOKEN_FALSE: return String_make("TOKEN_FALSE");
	
    case TOKEN_FN: return String_make("TOKEN_FN");
    case TOKEN_RETURN: return String_make("TOKEN_RETURN");
    case TOKEN_IF: return String_make("TOKEN_IF");
    case TOKEN_ELSE: return String_make("TOKEN_ELSE");
    case TOKEN_CONTINUE: return String_make("TOKEN_CONTINUE");
    case TOKEN_BREAK: return String_make("TOKEN_BREAK");
    case TOKEN_FOR: return String_make("TOKEN_FOR");
    case TOKEN_WHILE: return String_make("TOKEN_WHILE");

    case TOKEN_LPAREN: return String_make("TOKEN_LPAREN");
    case TOKEN_RPAREN: return String_make("TOKEN_RPAREN");
    case TOKEN_LBRACE: return String_make("TOKEN_LBRACE");
    case TOKEN_RBRACE: return String_make("TOKEN_RBRACE");
    case TOKEN_LBRACKET: return String_make("TOKEN_LBRACKET");
    case TOKEN_RBRACKET: return String_make("TOKEN_RBRACKET");
    case TOKEN_SEMICOLON: return String_make("TOKEN_SEMICOLON");
    case TOKEN_COLON: return String_make("TOKEN_COLON");
    case TOKEN_DOT: return String_make("TOKEN_DOT");
    case TOKEN_COMMA: return String_make("TOKEN_COMMA");

    case TOKEN_PLUS: return String_make("TOKEN_PLUS");
    case TOKEN_MINUS: return String_make("TOKEN_MINUS");
    case TOKEN_MULTIPLY: return String_make("TOKEN_MULTIPLY");
    case TOKEN_DIVIDE: return String_make("TOKEN_DIVIDE");
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
