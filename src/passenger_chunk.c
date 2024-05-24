#include "passenger_chunk.h"

Chunk Chunk_make() {
    Chunk chunk = {};
    return chunk;
}

void Chunk_free(Chunk* chunk) {
}

void Chunk_write_opcode(Chunk* chunk, Opcode* opcode) {
}

void Chunk_write_operand(Chunk* chunk, Value* operand) {
}

Opcode* Chunk_decode_opcode(Chunk* chunk, i32 pos) {
    return (Opcode*)&chunk->code[pos];
}

Value* Chunk_decode_operand(Chunk* chunk, i32 pos) {
    return (Value*)&chunk->code[pos];
}
