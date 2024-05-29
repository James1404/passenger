#include "passenger_parser.h"

#include <stdlib.h>

static void Parser_advance(Parser* parser) {
    parser->position++;
}

static Token Parser_current(Parser* parser) {
    return TokenArray_at(parser->tokens, parser->position);
}

static bool Parser_match(Parser* parser, TokenType expected) {
    if(Parser_current(parser).type == expected) {
        Parser_advance(parser);
        return true;
    }

    return false;
}


static void Parse_value(Parser* parser) {
    Token current = Parser_current(parser);
    Parser_advance(parser);

    switch(current.type) {
        case TOKEN_IDENTIFIER: {
                                   // todo
            break;
        }

        case TOKEN_MINUS: {
            Token num = Parser_current(parser);
            Parser_advance(parser);
            Value v = Value_from_number(strtod(String_get_raw(num.text), NULL));
            v.ptr.number = -v.ptr.number;
            
            Chunk_push_value(&parser->chunk, v);
            break;
        }
        case TOKEN_NUMBER: {
            Value v = Value_from_number(strtod(String_get_raw(current.text), NULL));
            Chunk_push_value(&parser->chunk, v);
            break;
        }

        case TOKEN_STRING: {
            Value v = Value_from_string(current.text);
            Chunk_push_value(&parser->chunk, v);
            break;
        }

        case TOKEN_FALSE: {
            Value v = Value_from_bool(false);
            Chunk_push_value(&parser->chunk, v);
            break;
        }
        case TOKEN_TRUE: {
            Value v = Value_from_bool(true);
            Chunk_push_value(&parser->chunk, v);
            break;
        }
        default:
            break;
    }
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
