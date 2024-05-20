#include "passenger_string.h"

#include "string.h"

String make_string(const char* raw) {
    String r = {};

    r.data = raw;
    r.length = strlen(raw);

    return r;
}

void free_string(String* str) { /* Might not implement */ }

char index_string(String str, int pos) {
    return str.data[pos];
}

String substring(String other, int pos, int length) {
    String r = {};
    r.data = &other.data[pos];
    r.length = length;
    return r;
}
