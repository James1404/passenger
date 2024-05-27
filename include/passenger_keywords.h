#ifndef PASSENGER_KEYWORDS_H
#define PASSENGER_KEYWORDS_H

#include "passenger_lex.h"

// The source file is generated using gperf.
//
// --- COMMAND ---
// cd src/
// gperf passenger.gperf > passenger_keywords.c
// --- COMMAND ---


TokenType Passenger_GetKeyword(Token t);

#endif//PASSENGER_KEYWORDS_H
