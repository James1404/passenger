#ifndef PASSENGER_VM_H
#define PASSENGER_VM_H

#include "passenger_opcodes.h"
#include "passenger_value.h"
#include "passenger_chunk.h"
#include "passenger_types.h"

typedef struct {
    int ip;
    Chunk* chunk;
    DynamicArray constants;
} VM;

VM VM_make(Chunk* chunk);
void VM_free(VM* vm);
void VM_run(VM* vm);

#endif//PASSENGER_VM_H
