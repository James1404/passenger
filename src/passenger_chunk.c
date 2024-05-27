#include "passenger_chunk.h"

#include <stdlib.h>

//
// --- ConstantsTable ---
//

ConstantsTable ConstantsTable_make() {
    return (ConstantsTable) {
        .allocated = 8,
        .length = 0,
        .data = NULL,
    };
}
void ConstantsTable_free(ConstantsTable* table) {
    if(table->data) free(table->data);
    *table = ConstantsTable_make();
}

u64 ConstantsTable_push(ConstantsTable* table, Value constant) {
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

Value ConstantsTable_get(ConstantsTable* table, u64 index) {
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

        .constants = ConstantsTable_make(),
    };
}

void Chunk_free(Chunk* chunk) {
    if(chunk->data) free(chunk->data);
    *chunk = Chunk_make();

    ConstantsTable_free(&chunk->constants);
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
    u64 index = ConstantsTable_push(&chunk->constants, val);

    u8* index_arr = (u8*)index;

    if(index <= U8_MAX) {
        Chunk_push_opcode(chunk, LOAD_CONST_CHAR);
        Chunk_push_byte(chunk, index_arr[0]);
    }
    else if(index <= U16_MAX) {
        Chunk_push_opcode(chunk, LOAD_CONST_SHORT);
        Chunk_push_byte(chunk, index_arr[0]);
        Chunk_push_byte(chunk, index_arr[1]);
    }
    else if(index <= U32_MAX) {
        Chunk_push_opcode(chunk, LOAD_CONST_LONG);
        Chunk_push_byte(chunk, index_arr[0]);
        Chunk_push_byte(chunk, index_arr[1]);
        Chunk_push_byte(chunk, index_arr[2]);
        Chunk_push_byte(chunk, index_arr[3]);
    }
    else if(index <= U64_MAX) {
        Chunk_push_opcode(chunk, LOAD_CONST_LONGLONG);
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
