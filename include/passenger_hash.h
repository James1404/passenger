#ifndef PASSENGER_HASH_H
#define PASSENGER_HASH_H

#include "passenger_common.h"
#include "passenger_value.h"

typedef u32 Hash;

#define DEFINE_HASH_FN(T, p) Hash hash_##T(void* opaque)
#define GET_HASH_FN(T, v) hash_##T((void*)v)

#define CAST_OPAQUE(v, T) (T*)v

DEFINE_HASH_FN(String, value);
DEFINE_HASH_FN(i32, value);

typedef Hash (*HashFn)(void* opaque);

typedef struct {
    String key;
    Value value;
} HashEntry;

typedef struct {
    i32 allocated, length;
    HashEntry* entries;
} HashMap;

HashMap HashMap_make();
void HashMap_free(HashMap* hashmap);

void HashMap_set(HashMap* hashmap, String key, Value value);

#endif//PASSENGER_HASH_H
