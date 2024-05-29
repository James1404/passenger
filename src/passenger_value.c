#include "passenger_value.h"

void Value_set_number(Value* value, f64 v) {
    value->ptr.number = v;
    value->type = VALUE_NUMBER;
}

void Value_set_string(Value* value, String v) {
    value->ptr.string = v;
    value->type = VALUE_STRING;
}

void Value_set_bool(Value* value, bool v) {
    value->ptr.boolean = v;
    value->type = VALUE_BOOLEAN;
}

Value Value_from_number(f64 v) {
    return (Value) {
        .ptr.number = v,
        .type = VALUE_NUMBER,
    };
}

Value Value_from_string(String v) {
    return (Value) {
        .ptr.string = v,
        .type = VALUE_STRING,
    };
}

Value Value_from_bool(bool v) {
    return (Value) {
        .ptr.boolean = v,
        .type = VALUE_BOOLEAN,
    };
}
