#ifndef PASSENGER_HASH_H
#define PASSENGER_HASH_H

#include "passenger_common.h"
#include "passenger_value.h"

typedef usize Hash;

#define DEFINE_HASH_FN(T, p) Hash hash_##T(void* opaque)
#define GET_HASH_FN(T, v) hash_##T((void*)v)

#define CAST_OPAQUE(v, T) (T*)v

DEFINE_HASH_FN(String, value);
DEFINE_HASH_FN(i32, value);

typedef Hash (*HashFn)(void* opaque);

//
// --- Hash Map ---
//
typedef struct HashMapEntry {
    Hash hash;

    String key;
    Value value;

    struct HashMapEntry* next;
} HashMapEntry;

typedef struct {
    usize allocated, length;
    HashMapEntry* buckets;
} HashMap;

HashMap HashMap_make();
void HashMap_free(HashMap* hashmap);

void HashMap_set(HashMap* hashmap, String key, Value value);
Value HashMap_get(HashMap* hashmap, String key);

Value HashMap_exists(HashMap* hashmap, String key);

//
// --- Hash Set ---
//

typedef struct HashSetEntry {
    Hash hash;
    String key;

    struct HashSetEntry* next;
} HashSetEntry;

typedef struct {
    usize allocated, length;
    HashSetEntry* buckets;
} HashSet;

HashSet HashSet_make();
void HashSet_free(HashSet* hashset);

void HashSet_add(HashSet* hashset, String key, Value value);
bool HashSet_has(HashSet* hashset, String key);

#endif//PASSENGER_HASH_H
