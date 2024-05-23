#include "passenger_vm.h"

VM VM_make(Chunk* chunk) {
    VM vm = {};

    vm.ip = 0;
    vm.chunk = chunk;
    vm.constants = DynamicArray_make(sizeof(Value));

    return vm;
}

void VM_free(VM* vm) {
    Chunk_free(vm->chunk);
    DynamicArray_free(&vm->constants);
}

void VM_run(VM* vm) {
    while(vm->ip < vm->chunk->size) {
    }
}
