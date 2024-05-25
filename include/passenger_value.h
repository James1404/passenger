#ifndef PASSENGER_VALUE_H
#define PASSENGER_VALUE_H

#include "passenger_common.h"

#define VALUE(name) VALUE_##name

typedef struct {
    union {
        f64 number;
        String string;
        bool boolean;
    } ptr;
    enum {
        VALUE(NUMBER),
        VALUE(STRING),
        VALUE(BOOLEAN),
    } type;
} Value;

Value Value_make_number(f64 val);
Value Value_make_string(String val);
Value Value_make_bool(bool val);

#endif//PASSENGER_VALUE_H
