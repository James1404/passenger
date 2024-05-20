#ifndef PASSENGER_STRING_H
#define PASSENGER_STRING_H

typedef struct {
    const char* data;
    int length;
} String;

String make_string(const char* raw);
void free_string(String* str);

char index_string(String str, int pos);
String substring(String other, int pos, int length);

#endif//PASSENGER_STRING_H
