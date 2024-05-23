#include "passenger_hash.h"

#include <stdlib.h>

//
// --- Hash Functions ---
//
DEFINE_HASH_FN(String, opaque) {
    String* value = CAST_OPAQUE(opaque, String);

    Hash hash = 0;

    i32 prime = 0x125fadb;

    for(i32 i = 0; i < value->length; i++) {
        hash ^= (i32)value->data[i] + prime;
    }

    return hash;
}

DEFINE_HASH_FN(i32, opaque) {
    i32* value = CAST_OPAQUE(opaque, i32);
    return *value;
}

//
// --- Hash Map ---
//

static void allocate_hashmap(HashMap* hashmap) {
    hashmap->bucket = malloc(hashmap->capacity * hashmap->valuesize);
}

HashMap make_hashmap(HashFn hash, i32 valuesize) {
    HashMap r = {};

    r.capacity = 100;
    r.size = 0;
    r.valuesize = valuesize;
    r.hash = hash;

    allocate_hashmap(&r);

    return r;
}

void free_hashmap(HashMap* hashmap) {
}

void hashmap_insert(HashMap* hashmap, void* key, void* value){
    Hash hash = hashmap->hash(key) % hashmap->capacity;
    hashmap->size++;

    if(hashmap->size >= hashmap->capacity) {
        allocate_hashmap(hashmap);
    }
}
