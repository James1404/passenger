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
