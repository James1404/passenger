#include "passenger_chunk.h"

#include <stdlib.h>

Chunk Chunk_make() {
    return (Chunk) {
        .allocated = 8,
        .length = 0,
        .data = NULL
    };
}

void Chunk_free(Chunk* chunk) {
    if(chunk->data) free(chunk->data);
    *chunk = Chunk_make();
}

void Chunk_write_byte(Chunk* chunk, byte val) {
}
