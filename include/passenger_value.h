#ifndef PASSENGER_VALUE_H
#define PASSENGER_VALUE_H

#include "passenger_common.h"

#define VALUE(name) VALUE_##name

typedef struct {
    union {
        f64 number;
        String string;
        b32 boolean;
    } ptr;
    enum {
        VALUE(NUMBER),
        VALUE(STRING),
        VALUE(BOOLEAN),
    } type;
} Value;

#endif//PASSENGER_VALUE_H
