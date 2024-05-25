#include "passenger_value.h"

Value Value_make_number(f64 val) {
    Value r = {};

    r.ptr.number = val;
    r.type = VALUE_NUMBER;

    return r;
}

Value Value_make_string(String val) {
    Value r = {};

    r.ptr.string = val;
    r.type = VALUE_STRING;

    return r;
}

Value Value_make_bool(bool val) {
    Value r = {};

    r.ptr.boolean = val;
    r.type = VALUE_BOOLEAN;

    return r;
}
