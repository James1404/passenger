#include "passenger_opcodes.h"

String Opcode_tostring(u8 op) {
    switch(op) {
#define DO(X) case X: return String_make(#X);
        FOR_OPCODES(DO)
#undef DO
        default: return String_make("OPCODE_INVALID");
    }
}
