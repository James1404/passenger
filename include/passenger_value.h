#ifndef PASSENGER_VALUE_H
#define PASSENGER_VALUE_H

#include "stdbool.h"

#define VALUE(name) VALUE_##name

typedef struct {
    union {
        double number;
        const char* string;
        bool boolean;
    } ptr;
    enum {
        VALUE(NUMBER),
        VALUE(STRING),
        VALUE(BOOLEAN),
    } type;
} Value;

#endif//PASSENGER_VALUE_H
