#ifndef PASSENGER_CHUNK_H
#define PASSENGER_CHUNK_H

#include "passenger_opcodes.h"
#include "passenger_value.h"

typedef struct {
    int capacity, size;
    void* code;
} Chunk;

Chunk make_chunk();
void free_chunk(Chunk* chunk);

void write_opcode_chunk(Chunk* chunk, Opcode* opcode);
void write_operand_chunk(Chunk* chunk, Value* operand);

Opcode* decode_opcode(Chunk* chunk, int pos);
Value* decode_operand(Chunk* chunk, int pos);

#endif//PASSENGER_CHUNK_H
