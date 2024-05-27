#ifndef PASSENGER_OPCODES_H
#define PASSENGER_OPCODES_H

#include "passenger_common.h"
#define FOR_OPCODES(DO)\
    DO(LOAD_CONST_CHAR)\
    DO(LOAD_CONST_SHORT)\
    DO(LOAD_CONST_LONG)\
    DO(LOAD_CONST_LONGLONG)\
    \
    DO(JUMP_REL)\
    DO(JUMP_ABS)\
    \
    DO(PUSH)\
    DO(POP)\

typedef enum {
#define DO(x) x,
    FOR_OPCODES(DO)
#undef DO
} Opcode;

String Opcode_tostring(u8 op);

#endif//PASSENGER_OPCODES_H
