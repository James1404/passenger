#ifndef PASSENGER_VALUE_H
#define PASSENGER_VALUE_H

#include "passenger_common.h"

typedef struct {
    union {
        f64 number;
        String string;
        bool boolean;
    } ptr;
    enum {
        VALUE_NUMBER,
        VALUE_STRING,
        VALUE_BOOLEAN,
    } type;
} Value;

void Value_set_number(Value* value, f64 v);
void Value_set_string(Value* value, String v);
void Value_set_bool(Value* value, bool v);

Value Value_from_number(f64 v);
Value Value_from_string(String v);
Value Value_from_bool(bool v);

#endif//PASSENGER_VALUE_H
