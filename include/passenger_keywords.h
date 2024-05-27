#ifndef PASSENGER_KEYWORDS_H
#define PASSENGER_KEYWORDS_H

#include "passenger_lex.h"

// The source file is generated using gperf.
//
// --- COMMAND ---
// gperf src/passenger_keywords.gperf > src/passenger_keywords.c
// --- COMMAND ---


TokenType Passenger_GetKeyword(Token t);

#endif//PASSENGER_KEYWORDS_H
