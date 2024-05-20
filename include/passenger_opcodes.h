#ifndef PASSENGER_OPCODES_H
#define PASSENGER_OPCODES_H

#define OPCODE(name) CODE_##name

typedef enum {
    LOAD_CONST_CHAR,     // 8  bit
    LOAD_CONST_SHORT,    // 16 bit
    LOAD_CONST_LONG,     // 32 bit
    LOAD_CONST_LONGLONG, // 64 bit

    JUMP_REL,
    JUMP_ABS,

    PUSH, POP,
} Opcode;

#endif//PASSENGER_OPCODES_H
