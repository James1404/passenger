#include "passenger_parser.h"

static void Parser_advance(Parser* parser) {
    parser->position++;
}

static Token Parser_current(Parser* parser) {
    return TokenArray_at(parser->tokens, parser->position);
}

Parser Parser_make(TokenArray* tokens) {
    return (Parser) {
        .position = 0,
        .tokens = tokens,
        .chunk = Chunk_make()
    };
}

void Parser_free(Parser* parser) {
    Chunk_free(&parser->chunk);
}

void Parser_emit(Parser* parser) {
}
