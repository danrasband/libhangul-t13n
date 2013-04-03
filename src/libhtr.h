/**
 * Copyright 2013 Daniel Rasband <danrasband@gmail.com>
 */


#ifndef __LIBHANGUL_ROMAJA_H__
#define __LIBHANGUL_ROMAJA_H__

#include <stdlib.h>
#include "common.h"
#include "hangul.h"
#include "romaja.h"

typedef enum {
  YALE,
  REVISED_ROMANIZATION,
  MCCUNE_REISCHAUER,
  KONTSEVICH,
  SKATS
} ROMANIZATION_SYSTEM;

size_t romanize_hangul(char* orig, char* dest, size_t buffer_size, ROMANIZATION_SYSTEM system);
size_t hangulize_romaja(char* orig, char* dest, size_t buffer_size, ROMANIZATION_SYSTEM system);

#endif
