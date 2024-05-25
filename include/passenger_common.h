#ifndef PASSENGER_TYPES_H
#define PASSENGER_TYPES_H

#include <stdbool.h>
#include <string.h>

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned long       u32;
typedef unsigned long long  u64;

typedef char        i8;
typedef short       i16;
typedef long        i32;
typedef long long   i64;

typedef char            byte;
typedef unsigned char   ubyte;

typedef float f32;
typedef long double f64;

typedef size_t usize;

//
// --- String ---
//

typedef struct {
    byte* data;
    i32 length;
} String;

String String_make(const byte* raw);
void String_free(String* str);

byte String_index(String str, i32 pos);
String String_substr(String other, i32 pos, i32 length);

const byte* String_get_raw(String str);

//
// --- Dynamic Array ---
//

typedef struct {
    byte* data;
    u64 element_size;

    u64 capacity, length;
} DynamicArray;

DynamicArray DynamicArray_make(u64 element_size);
void DynamicArray_free(DynamicArray* array);

void DynamicArray_push(DynamicArray* array, void* elem);

#define DynamicArray_at(T, array, i) (T*)((array).data + i)

#endif//PASSENGER_TYPES_H
