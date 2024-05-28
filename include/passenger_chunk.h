#ifndef PASSENGER_CHUNK_H
#define PASSENGER_CHUNK_H

#include "passenger_common.h"
#include "passenger_opcodes.h"
#include "passenger_value.h"

typedef struct {
    u64 allocated, length;
    Value* data;
} LiteralTable;

LiteralTable LiteralTable_make();
void LiteralTable_free(LiteralTable* table);

u64 LiteralTable_push(LiteralTable* table, Value constant);
Value LiteralTable_get(LiteralTable* table, u64 index);

typedef struct {
    u64 allocated, length;
    u8* data;

    LiteralTable literals;
} Chunk;

Chunk Chunk_make();
void Chunk_free(Chunk* chunk);

void Chunk_push_byte(Chunk* chunk, byte val);

void Chunk_push_opcode(Chunk* chunk, Opcode op);
void Chunk_push_value(Chunk* chunk, Value val);

#endif//PASSENGER_CHUNK_H
