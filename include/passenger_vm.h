#ifndef PASSENGER_VM_H
#define PASSENGER_VM_H

#include "passenger_opcodes.h"
#include "passenger_value.h"
#include "passenger_chunk.h"


typedef struct {
    int capacity, size;
    Value* data;
} ConstantsTable;

ConstantsTable make_constants_table();
void free_constants_table(ConstantsTable* table);
int add_constants_table(ConstantsTable* table, Value* constant);

typedef struct {
    int ip;
    Chunk* chunk;
    ConstantsTable constants;
} VM;

VM make_vm(Chunk* chunk);
void free_vm(VM* vm);
void run_vm(VM* vm);

#endif//PASSENGER_VM_H
