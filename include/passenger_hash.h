#ifndef PASSENGER_HASH_H
#define PASSENGER_HASH_H

#include "passenger_types.h"

typedef u64 Hash;

#define DEFINE_HASH_FN(T, p) Hash hash_##T(void* opaque)
#define GET_HASH_FN(T) hash_##T

#define CAST_OPAQUE(v, T) (T*)v

DEFINE_HASH_FN(String, value);
DEFINE_HASH_FN(i32, value);

typedef Hash (*HashFn)(void* opaque);

typedef struct {
    i32 capacity, size;
    Hash* bucket;

    i32 valuesize;

    HashFn hash;
} HashMap;

HashMap make_hashmap(HashFn hash, i32 valuesize);
void free_hashmap(HashMap* hashmap);

void hashmap_insert(HashMap* hashmap, void* key, void* value);

#define HASHMAP(K, V) make_hash(GET_HASH_FN(T), sizeof(V));

#endif//PASSENGER_HASH_H
