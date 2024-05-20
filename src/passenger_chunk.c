#include "passenger_chunk.h"

#include "passenger_string.h"

#include <stdbool.h>

Chunk make_chunk() {
    Chunk chunk = {};
    return chunk;
}
void free_chunk(Chunk* chunk) {}

void write_opcode_chunk(Chunk* chunk, Opcode* opcode) {
}
void write_operand_chunk(Chunk* chunk, Value* operand) {
}

Opcode* decode_opcode(Chunk* chunk, int pos) {
    return (Opcode*)&chunk->code[pos];
}

Value* decode_operand(Chunk* chunk, int pos) {
    return (Value*)&chunk->code[pos];
}
