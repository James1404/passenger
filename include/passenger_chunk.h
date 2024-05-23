#ifndef PASSENGER_CHUNK_H
#define PASSENGER_CHUNK_H

#include "passenger_types.h"
#include "passenger_opcodes.h"
#include "passenger_value.h"

typedef struct {
    i32 capacity, size;
    u8* code;
} Chunk;

Chunk Chunk_make();
void Chunk_free(Chunk* chunk);

void Chunk_write_opcode(Chunk* chunk, Opcode* opcode);
void Chunk_write_operand(Chunk* chunk, Value* operand);

Opcode* Chunk_decode_opcode(Chunk* chunk, i32 pos);
Value* Chunk_decode_operand(Chunk* chunk, i32 pos);

#endif//PASSENGER_CHUNK_H
