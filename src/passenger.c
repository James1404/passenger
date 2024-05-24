#include "passenger.h"

#include "passenger_common.h"
#include "passenger_lex.h"
#include "passenger_error.h"

#include <stdio.h>
#include <stdlib.h>

void Passenger_run(const char* src) {
    printf("Input: \"%s\"\n", src);

    Lexer l = Lexer_make(String_make(src));
    Lexer_run(&l);

    printf("--- Output ---\n");
    for(i32 i = 0; i < l.tokens.len; i++) {
        Token t = TokenArray_at(&l.tokens, i);
        String ty = TokenType_tostring(t.type);
        printf("%s \"%s\"\n", String_get_raw(ty), String_get_raw(t.text));
    }

    Lexer_free(&l);
}

void Passenger_run_file(const char* path) {
    FILE* file = fopen(path, "r");

    if(!file) {
        Passenger_error("Couldnt not find file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);

    fseek(file, 0, SEEK_SET);
    char* buffer = malloc(length);

    fread(buffer, 1, length, file);
    fclose(file);

    Passenger_run(buffer);

    free(buffer);
}
