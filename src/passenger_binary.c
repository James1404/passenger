#include "passenger.h"
#include "passenger_error.h"

#include <stdio.h>

void error(const char* msg, ErrorSeverity severity) {
    printf("%s\n", msg);
}

int main() {
    Passenger_set_error_callback(&error);
    Passenger_run_file("test/test.psg");
}
