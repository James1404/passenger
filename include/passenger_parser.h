#ifndef PASSENGER_PARSER_H
#define PASSENGER_PARSER_H

#include "passenger_chunk.h"
#include "passenger_common.h"
#include "passenger_lex.h"

typedef struct {
    u64 position;
    TokenArray* tokens;
    Chunk chunk;
} Parser;

Parser Parser_make(TokenArray* tokens);
void Parser_free(Parser* parser);

void Parser_emit(Parser* parser);

#endif//PASSENGER_PARSER_H
