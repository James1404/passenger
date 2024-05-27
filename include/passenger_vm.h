#ifndef PASSENGER_VM_H
#define PASSENGER_VM_H

#include "passenger_hash.h"
#include "passenger_chunk.h"
#include "passenger_common.h"

typedef struct {
    Value value;
    u64 scope;
} Local;

typedef struct {
    u64 top, allocated;
    Local* data;

    u64 scope;
} Stack;

Stack Stack_make();
void Stack_free(Stack* stack);

Local Stack_top(Stack* stack);
void Stack_push(Stack* stack, Value elem);
void Stack_pop(Stack* stack);

void Stack_inc(Stack* stack);
void Stack_dec(Stack* stack);

typedef struct {
    int ip;
    Chunk* chunk;
    HashMap values;

    Stack stack;
} VM;

VM VM_make(Chunk* chunk);
void VM_free(VM* vm);
void VM_run(VM* vm);

Opcode VM_decode_opcode(VM* vm);
Value VM_decode_operand(VM* vm);

#endif//PASSENGER_VM_H
