#include "passenger.h"

#include "passenger_chunk.h"

#include <stdio.h>
#include <stdlib.h>

static ErrorCallback error_callback = NULL;

void run(const char* src) {
}

void run_file(const char* path) {
    FILE* file = fopen(path, "r");

    if(!file) {
        error_callback("Couldnt not find file", ErrorSeverity_Error);
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);

    fseek(file, 0, SEEK_SET);
    char* buffer = malloc(length);

    fread(buffer, 1, length, file);
    fclose(file);

    run(buffer);

    free(buffer);
}

void set_error_callback(ErrorCallback fn) {
    error_callback = fn;
}
