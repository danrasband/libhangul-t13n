/**
 * Copyright 2013 Daniel Rasband <danrasband@gmail.com>
 */


#ifndef __LIBHANGUL_T13N_H__
#define __LIBHANGUL_T13N_H__

#include <stdlib.h>

typedef enum {
  YALE,
  REVISED_ROMANIZATION,
  MCCUNE_REISCHAUER,
  KONTSEVICH,
  SKATS
} T13N_SYSTEM;

int transliterate_hangul(char* dest, size_t buffer_size, char* orig, T13N_SYSTEM system);
int hangulize_romaja(char* dest, size_t buffer_size, char* orig, T13N_SYSTEM system);

#endif
