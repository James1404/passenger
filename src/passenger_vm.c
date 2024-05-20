#include "passenger_vm.h"

#include <stdio.h>
#include <stdlib.h>

ConstantsTable make_constants_table() {
    ConstantsTable table = {};

    table.size = 0;
    table.capacity = 0;
    table.data = NULL;

    return table;
}

void free_constants_table(ConstantsTable* table) {
    if(table->data) free(table->data);
    table->data = NULL;
}

static void realloc_constants_table(ConstantsTable* table) {
    if(!table->data) {
        table->capacity = 8;
        table->data = malloc(sizeof(Value) * table->capacity);
        return;
    }

    if(table->size >= table->capacity) {
        table->capacity *= 2;
        table->data = realloc(table->data, table->capacity);
    }
};

int add_constants_table(ConstantsTable* table, Value* constant) {
    realloc_constants_table(table);
    memcpy(&table->data[++table->size], constant, sizeof(&constant));
    return table->size;
}

VM make_vm(Chunk* chunk) {
    VM vm = {};

    vm.ip = 0;
    vm.chunk = chunk;
    vm.constants = make_constants_table();

    return vm;
}

void free_vm(VM* vm) {
    free_chunk(vm->chunk);
    free_constants_table(&vm->constants);
}

void run_vm(VM* vm) {
    while(vm->ip < vm->chunk->size) {
    }
}
