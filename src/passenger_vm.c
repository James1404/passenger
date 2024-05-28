#include "passenger_vm.h"
#include "passenger_opcodes.h"
#include "passenger_value.h"

#include <stdlib.h>

//
// --- Variable Table ---
//

VariableTable VariableTable_make() {
    return (VariableTable) {
        .top = 0,
        .allocated = 8,
        .data = NULL,
        .scope = 0,
    };
}

void VariableTable_free(VariableTable* table) {
    if(table->data) free(table->data);
    *table = VariableTable_make();
}

Local VariableTable_top(VariableTable* table) {
    return table->data[table->top];
}

void VariableTable_push(VariableTable* table, Value elem, bool constant) {
    if(!table->data) {
        table->data = malloc(sizeof(Local) * table->allocated);
    }

    table->data[table->top] = (Local) {
        .value = elem,
        .constant = constant,
        .scope = table->scope,
    };

    table->top++;

    if(table->top >= table->allocated) {
        table->allocated *= 2;
        table->data = realloc(table->data, sizeof(Local) * table->allocated);
    }
}

void VariableTable_pop(VariableTable* table) {
    table->top--;
}

void VariableTable_inc(VariableTable* table) {
    table->scope++;
}
void VariableTable_dec(VariableTable* table) {
    table->scope--;

    while(VariableTable_top(table).scope > table->scope) {
        VariableTable_pop(table);
    }
}

//
// --- Stack ---
//

Stack Stack_make() {
    return (Stack) {
        .top = 0,
        .allocated = 8,
        .data = NULL,
    };
}

void Stack_free(Stack* stack) {
    if(stack->data) free(stack->data);
    *stack = Stack_make();
}

Value Stack_top(Stack* stack) {
    return stack->data[stack->top];
}

void Stack_push(Stack* stack, Value value) {
    if(!stack->data) {
        stack->data = malloc(sizeof(Local) * stack->allocated);
    }

    stack->data[stack->top] = value;
    stack->top++;

    if(stack->top >= stack->allocated) {
        stack->allocated *= 2;
        stack->data = realloc(stack->data, sizeof(Local) * stack->allocated);
    }
}

void Stack_pop(Stack* stack) {
    stack->top--;
}

//
// --- Call Stack ---
//

CallStack CallStack_make() {
    return (CallStack) {
        .top = 0,
        .allocated = 8,
        .data = NULL,
    };
}

void CallStack_free(CallStack* stack) {
    if(stack->data) free(stack->data);
    *stack = CallStack_make();
}

u64 CallStack_top(CallStack* stack) {
    return stack->data[stack->top];
}

void CallStack_push(CallStack* stack, u64 loc) {
    if(!stack->data) {
        stack->data = malloc(sizeof(Local) * stack->allocated);
    }

    stack->data[stack->top] = loc;
    stack->top++;

    if(stack->top >= stack->allocated) {
        stack->allocated *= 2;
        stack->data = realloc(stack->data, sizeof(Local) * stack->allocated);
    }
}

void CallStack_pop(CallStack* stack) {
    stack->top--;
}

//
// --- VM ---
//

VM VM_make(Chunk* chunk) {
    return (VM) {
        .ip = 0,
        .chunk = chunk,
        .values = HashMap_make(),
        .variables = VariableTable_make(),
        .stack = Stack_make(),
    };
}

void VM_free(VM* vm) {
    Chunk_free(vm->chunk);
    HashMap_free(&vm->values);
    VariableTable_free(&vm->variables);
    Stack_free(&vm->stack);
}

void VM_run(VM* vm) {
    while(vm->ip < vm->chunk->length) {
        Opcode op = VM_decode_opcode(vm);

        vm->ip++;

        switch(op) {
            case LOAD_LITERAL_CHAR:
            case LOAD_LITERAL_SHORT:
            case LOAD_LITERAL_LONG:
            case LOAD_LITERAL_LONGLONG:

            case JUMP_IF_TRUE:
            case JUMP_IF_FALSE: {
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

            case STORE: { break; }
            case LOAD: { break; }

            case MAKE_CONST: { break; }
            
            case ADD: {
                Value l = Stack_top(&vm->stack); Stack_pop(&vm->stack);
                Value r = Stack_top(&vm->stack); Stack_pop(&vm->stack);

                Value result = {};
                Value_set_number(&result, l.ptr.number + r.ptr.number);
                Stack_push(&vm->stack, result);
                break;
            }
            case SUB: {
                Value l = Stack_top(&vm->stack); Stack_pop(&vm->stack);
                Value r = Stack_top(&vm->stack); Stack_pop(&vm->stack);

                Value result = {};
                Value_set_number(&result, l.ptr.number - r.ptr.number);
                Stack_push(&vm->stack, result);
                break;
            }
            case MUL: {
                Value l = Stack_top(&vm->stack); Stack_pop(&vm->stack);
                Value r = Stack_top(&vm->stack); Stack_pop(&vm->stack);

                Value result = {};
                Value_set_number(&result, l.ptr.number * r.ptr.number);
                Stack_push(&vm->stack, result);
                break;
            }
            case DIV: {
                Value l = Stack_top(&vm->stack); Stack_pop(&vm->stack);
                Value r = Stack_top(&vm->stack); Stack_pop(&vm->stack);

                Value result = {};
                Value_set_number(&result, l.ptr.number / r.ptr.number);
                Stack_push(&vm->stack, result);
                break;
            }

            case LESS: {
                Value l = Stack_top(&vm->stack); Stack_pop(&vm->stack);
                Value r = Stack_top(&vm->stack); Stack_pop(&vm->stack);

                Value result = {};
                Value_set_bool(&result, l.ptr.number < r.ptr.number);
                Stack_push(&vm->stack, result);

                break;
            }
            case GREATER: {
                Value l = Stack_top(&vm->stack); Stack_pop(&vm->stack);
                Value r = Stack_top(&vm->stack); Stack_pop(&vm->stack);

                Value result = {};
                Value_set_bool(&result, l.ptr.number > r.ptr.number);
                Stack_push(&vm->stack, result);

                break;
            }

            case EQ: { break; }
            case NEQ: { break; }
            case LEQ: { break; }
            case GEQ: { break; }

        }
    }
}

Opcode VM_decode_opcode(VM* vm) {
    return *(Opcode*)&vm->chunk->data[++vm->ip];
}

Value VM_decode_operand(VM* vm) {
    return *(Value*)&vm->chunk->data[++vm->ip];
}

