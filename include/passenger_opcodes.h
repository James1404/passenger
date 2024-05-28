#ifndef PASSENGER_OPCODES_H
#define PASSENGER_OPCODES_H

typedef enum {
/*-----------
L: Literal table index
I: 64 bit index
N: Name of varible identifier
S: Value popped from stack

name                     args       desc
------------- */
LOAD_LITERAL_CHAR,//     L          load a literal using an 8 bit index
LOAD_LITERAL_SHORT,//    L          load a literal using an 16 bit index
LOAD_LITERAL_LONG,//     L          load a literal using an 32 bit index
LOAD_LITERAL_LONGLONG,// L          load a literal using an 64 bit index

JUMP_IF_TRUE,//          I          Move "IP" to "I" if stack top is true
JUMP_IF_FALSE,//         I          Move "IP" to "I" if stack top is false
PUSH,//                  L          Push literal value onto stack
POP,//                              Pop value of off stack

STORE,//                 N          Assign stack value to variable "N"
LOAD,//                  N          Push value of variable "N" onto the stack
MAKE_CONST,//            N          Assign stack value to variable "N"

ADD,//                              Add the two top stack values together, pushing the result back onto the stack
SUB,//                              Subtract the two top stack values from each other, pushing the result back onto the stack
MUL,//                              Multiply the two top stack values together, pushing the result back onto the stack
DIV,//                              Divide the two top stack values, and push the result onto the stack

LESS,//                             Compare the two top stack values, return comparison
GREATER,//                          Compare the two top stack values, return comparison

EQ,//
NEQ,//
LEQ,//
GEQ,//
} Opcode;

#endif//PASSENGER_OPCODES_H
