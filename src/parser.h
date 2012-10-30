/**
 * Copyright 2012 Daniel C. Rasband.
 */
#ifndef __hangeul_romaja_parser_h__
#define __hangeul_romaja_parser_h__

#include <stdbool.h>
#include "hangeul-romaja.h"
#include "types.h"

bool hangeul_parse_str(Hangeul **hangeulRef, size_t size, const char *source);
bool romaja_parse_str(Romaja **romajaRef, size_t size, const char *source);

#endif
