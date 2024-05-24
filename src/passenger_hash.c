#include "passenger_hash.h"

#include <stdlib.h>

//
// --- Hash Functions ---
//
DEFINE_HASH_FN(String, opaque) {
    String* value = CAST_OPAQUE(opaque, String);

    u32 b = 378551;
    u32 a = 63689;

    Hash hash = 0;

    for(i32 i = 0; i < value->length; i++) {
        char c = value->data[i];
        hash = hash * a + c;
        a = a * b;
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
    hashmap->entries = malloc(hashmap->allocated * sizeof(Value));
}

HashMap HashMap_make() {
    return (HashMap) {
        .entries = NULL,
        .allocated = 100,
        .length = 0,
    };
}

void free_hashmap(HashMap* hashmap) {
    free(hashmap->entries);
    *hashmap = HashMap_make();
}

void HashMap_set(HashMap* hashmap, String key, Value value) {
    Hash hash = GET_HASH_FN(String, &key) % hashmap->allocated;
    hashmap->length++;

    if(hashmap->length >= hashmap->allocated) {
        allocate_hashmap(hashmap);
    }
}
