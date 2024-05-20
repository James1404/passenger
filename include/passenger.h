#ifndef PASSENGER_H
#define PASSENGER_H

void run(const char* src);
void run_file(const char* path);

typedef enum {
    ErrorSeverity_Info,
    ErrorSeverity_Warning,
    ErrorSeverity_Error,
} ErrorSeverity;

typedef void (*ErrorCallback)(const char* msg, ErrorSeverity severity);
void set_error_callback(ErrorCallback fn);

#endif//PASSENGER_H
