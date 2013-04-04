/**
 * Copyright 2013 Daniel Rasband <danrasband@gmail.com>
 */


#ifndef __LIBHANGUL_T13N_H__
#define __LIBHANGUL_T13N_H__

#include "common.h"
#include "hangul.h"
#include "romaja.h"

typedef enum {
  YALE,
  REVISED_ROMANIZATION,
  MCCUNE_REISCHAUER,
  KONTSEVICH,
  SKATS
} T13N_SYSTEM;

size_t transliterate_hangul(char* orig, char* dest, size_t buffer_size, T13N_SYSTEM system);
size_t hangulize_romaja(char* orig, char* dest, size_t buffer_size, T13N_SYSTEM system);

#endif
