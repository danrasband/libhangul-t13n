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

int hangul_t13n_transliterate(char* dest, size_t buffer_size, char* orig, T13N_SYSTEM system);
int hangul_t13n_hangulize(char* dest, size_t buffer_size, char* orig, T13N_SYSTEM system);

#endif
