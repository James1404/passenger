#include "passenger_vm.h"
#include "passenger_opcodes.h"
#include "passenger_value.h"

#include <stdlib.h>

//
// --- Stack ---
//

Stack Stack_make() {
    return (Stack) {
        .top = 0,
        .allocated = 8,
        .data = NULL,
        .scope = 0,
    };
}

void Stack_free(Stack* stack) {
    if(stack->data) free(stack->data);
    *stack = Stack_make();
}

Local Stack_top(Stack* stack) {
    return stack->data[stack->top];
}

void Stack_push(Stack* stack, Value elem) {
    if(!stack->data) {
        stack->data = malloc(sizeof(Local) * stack->allocated);
    }

    stack->data[stack->top] = (Local) {
        .scope = stack->scope,
        .value = elem,
    };

    stack->top++;

    if(stack->top >= stack->allocated) {
        stack->allocated *= 2;
        stack->data = realloc(stack->data, sizeof(Local) * stack->allocated);
    }
}

void Stack_pop(Stack* stack) {
    stack->top--;
}

void Stack_inc(Stack* stack) {
    stack->scope++;
}
void Stack_dec(Stack* stack) {
    stack->scope--;

    while(Stack_top(stack).scope > stack->scope) {
        Stack_pop(stack);
    }
}

//
// --- VM ---
//

VM VM_make(Chunk* chunk) {
    return (VM) {
        .ip = 0,
        .chunk = chunk,
        .values = HashMap_make(),
        .stack = Stack_make(),
    };
}

void VM_free(VM* vm) {
    Chunk_free(vm->chunk);
    HashMap_free(&vm->values);
    Stack_free(&vm->stack);
}

void VM_run(VM* vm) {
    while(vm->ip < vm->chunk->length) {
        Opcode op = VM_decode_opcode(vm);

        vm->ip++;

        switch(op) {
            case LOAD_CONST_CHAR:
            case LOAD_CONST_SHORT:
            case LOAD_CONST_LONG:
            case LOAD_CONST_LONGLONG:

            case JUMP_REL:
            case JUMP_ABS: {
                break;
            }

            case PUSH: {
                Value v = VM_decode_operand(vm);
                Stack_push(&vm->stack, v);
                break;
            }
            case POP: {
                Stack_pop(&vm->stack);
                break;
            }
        }
    }
}

Opcode VM_decode_opcode(VM* vm) {
    return *(Opcode*)&vm->chunk->data[++vm->ip];
}

Value VM_decode_operand(VM* vm) {
    return *(Value*)&vm->chunk->data[++vm->ip];
}

