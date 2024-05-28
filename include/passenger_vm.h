#ifndef PASSENGER_VM_H
#define PASSENGER_VM_H

#include "passenger_hash.h"
#include "passenger_chunk.h"
#include "passenger_common.h"

typedef struct {
    Value value;
    bool constant;
    u64 scope;
} Local;

typedef struct {
    u64 top, allocated;
    Local* data;

    u64 scope;
} VariableTable;

VariableTable VariableTable_make();
void VariableTable_free(VariableTable* table);

Local VariableTable_top(VariableTable* table);
void VariableTable_push(VariableTable* table, Value elem, bool constant);
void VariableTable_pop(VariableTable* table);

void VariableTable_inc(VariableTable* table);
void VariableTable_dec(VariableTable* table);

typedef struct {
    u64 top, allocated;
    Value* data;
} Stack;

Stack Stack_make();
void Stack_free(Stack* stack);

Value Stack_top(Stack* stack);
void Stack_push(Stack* stack, Value value);
void Stack_pop(Stack* stack);

typedef struct {
    u64 top, allocated;
    u64* data;
} CallStack;

CallStack CallStack_make();
void CallStack_free(CallStack* stack);

u64 CallStack_top(CallStack* stack);
void CallStack_push(CallStack* stack, u64 loc);
void CallStack_pop(CallStack* stack);

typedef struct {
    int ip;
    Chunk* chunk;
    HashMap values;

    VariableTable variables;
    Stack stack;
} VM;

VM VM_make(Chunk* chunk);
void VM_free(VM* vm);
void VM_run(VM* vm);

Opcode VM_decode_opcode(VM* vm);
Value VM_decode_operand(VM* vm);

#endif//PASSENGER_VM_H
