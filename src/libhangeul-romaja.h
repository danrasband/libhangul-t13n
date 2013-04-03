/**
 * Copyright 2013 Daniel Rasband <danrasband@gmail.com>
 */


#ifndef __LIBHANGEUL_ROMAJA_H__
#define __LIBHANGEUL_ROMAJA_H__

#include <stdlib.h>
#include "common.h"
#include "hangeul.h"
#include "romaja.h"

typedef enum {
  YALE,
  REVISED_ROMANIZATION,
  MCCUNE_REISCHAUER,
  KONTSEVICH,
  SKATS
} ROMANIZATION_SYSTEM;

size_t romanize_hangeul(char* orig, char* dest, size_t buffer_size, ROMANIZATION_SYSTEM system);
size_t hangeulize_romaja(char* orig, char* dest, size_t buffer_size, ROMANIZATION_SYSTEM system);

#endif
