#ifndef PASSENGER_CHUNK_H
#define PASSENGER_CHUNK_H

#include "passenger_common.h"
#include "passenger_opcodes.h"
#include "passenger_value.h"

typedef struct {
    i32 allocated, length;
    u8* data;
} Chunk;

Chunk Chunk_make();
void Chunk_free(Chunk* chunk);

void Chunk_write_byte(Chunk* chunk, byte val);

#endif//PASSENGER_CHUNK_H
