#ifndef PASSENGER_ERROR_H
#define PASSENGER_ERROR_H

typedef enum {
    ErrorSeverity_Info,
    ErrorSeverity_Warning,
    ErrorSeverity_Error,
} ErrorSeverity;

typedef void (*ErrorCallback)(const char* msg, ErrorSeverity severity);
void Passenger_set_error_callback(ErrorCallback fn);

void Passenger_error(const char* msg);

#endif//PASSENGER_ERROR_H
