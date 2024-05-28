#include "passenger_chunk.h"

#include <stdlib.h>

//
// --- LiteralTable ---
//

LiteralTable LiteralTable_make() {
    return (LiteralTable) {
        .allocated = 8,
        .length = 0,
        .data = NULL,
    };
}
void LiteralTable_free(LiteralTable* table) {
    if(table->data) free(table->data);
    *table = LiteralTable_make();
}

u64 LiteralTable_push(LiteralTable* table, Value constant) {
    if(table->allocated == 0 || !table->data) {
        table->allocated = 8;
        table->data = malloc(table->allocated * sizeof(Value));
    }

    u64 index = table->length;
    table->data[index] = constant;
    table->length++;

    if(table->length >= table->allocated) {
        table->allocated *= 2;
        table->data = realloc(table->data, table->allocated * sizeof(Value));
    }

    return index;
}

Value LiteralTable_get(LiteralTable* table, u64 index) {
    return table->data[index];
}

//
// --- Chunk ---
//

Chunk Chunk_make() {
    return (Chunk) {
        .allocated = 8,
        .length = 0,
        .data = NULL,

        .literals = LiteralTable_make(),
    };
}

void Chunk_free(Chunk* chunk) {
    if(chunk->data) free(chunk->data);
    *chunk = Chunk_make();

    LiteralTable_free(&chunk->literals);
}

void Chunk_push_byte(Chunk* chunk, byte val) {
    if(chunk->allocated == 0 || !chunk->data) {
        chunk->allocated = 8;
        chunk->data = malloc(chunk->allocated * sizeof(Value));
    }

    chunk->data[chunk->length] = val;
    chunk->length++;

    if(chunk->length >= chunk->allocated) {
        chunk->allocated *= 2;
        chunk->data = realloc(chunk->data, chunk->allocated * sizeof(Value));
    }
}


void Chunk_push_opcode(Chunk* chunk, Opcode op) {
    Chunk_push_byte(chunk, op);
}

void Chunk_push_value(Chunk* chunk, Value val) {
    u64 index = LiteralTable_push(&chunk->literals, val);

    u8* index_arr = (u8*)index;

    if(index <= U8_MAX) {
        Chunk_push_opcode(chunk, LOAD_LITERAL_CHAR);
        Chunk_push_byte(chunk, index_arr[0]);
    }
    else if(index <= U16_MAX) {
        Chunk_push_opcode(chunk, LOAD_LITERAL_SHORT);
        Chunk_push_byte(chunk, index_arr[0]);
        Chunk_push_byte(chunk, index_arr[1]);
    }
    else if(index <= U32_MAX) {
        Chunk_push_opcode(chunk, LOAD_LITERAL_LONG);
        Chunk_push_byte(chunk, index_arr[0]);
        Chunk_push_byte(chunk, index_arr[1]);
        Chunk_push_byte(chunk, index_arr[2]);
        Chunk_push_byte(chunk, index_arr[3]);
    }
    else if(index <= U64_MAX) {
        Chunk_push_opcode(chunk, LOAD_LITERAL_LONGLONG);
        Chunk_push_byte(chunk, index_arr[0]);
        Chunk_push_byte(chunk, index_arr[1]);
        Chunk_push_byte(chunk, index_arr[2]);
        Chunk_push_byte(chunk, index_arr[3]);
        Chunk_push_byte(chunk, index_arr[4]);
        Chunk_push_byte(chunk, index_arr[5]);
        Chunk_push_byte(chunk, index_arr[6]);
        Chunk_push_byte(chunk, index_arr[7]);
    }
}
