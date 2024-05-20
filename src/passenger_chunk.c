#include "passenger_chunk.h"

#include "passenger_string.h"

#include <stdbool.h>

typedef struct {
    int position;
    String input;
} Parser;

Parser make_parser(String input) {
    Parser parser = {};
    parser.input = input;
    parser.position = 0;
    return parser;
}

void free_parser(Parser* parser) {
}

char current_parser(Parser* parser) {
    return index_string(parser->input, parser->position);
}

void advance_parser(Parser* parser) {
    parser->position++;
}

typedef enum {
    Keyword_var,
    Keyword_const,

    Keyword_if,
    Keyword_else,

    Keyword_continue,
    Keyword_break,

    Keyword_return,

    Keyword_Fn,
} Keyword;

static bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static bool isNumber(char c) {
    return c >= '0' && c <= '9';
}

static bool isWhitespace(char c) {
    switch(c) {
        case ' ':
        case '\t':
        case '\n':
        case '\r':
            return true;
        default:
            return false;
    }
}

static void consume_whitespace(Parser* parser) {
    while(isWhitespace(current_parser(parser))) advance_parser(parser);
}

static void consume_identifier(Parser* parser, char expected, String error) {
    int start = parser->position;
    if(isLetter(current_parser(parser))) {
        while(isLetter(current_parser(parser)) || isNumber(current_parser(parser))) advance_parser(parser);

        String id = substring(parser->input, start, parser->position);

        return;
    }
}

void run_parser(Parser* parser);
