/**
 * Copyright 2012 Daniel C. Rasband
 */
#ifndef __hangeul_romaja_h__
#define __hangeul_romaja_h__

#include <stdlib.h>

typedef enum RomanizationType {
	YALE,
	YALE_ORIGINAL,
	REVISED,
	MCCUNE_REISCHAUER
} RomanizationType;

/* Conversion from Hangeul (Romanization) */
int romanize(char *romaja, size_t size, const char *hangeul, RomanizationType rtype);
int hangeul_to_yale(char *romaja, size_t size, const char *hangeul);
int hangeul_to_yale_original(char *romaja, size_t size, const char *hangeul);
int hangeul_to_revised(char *romaja, size_t size, const char *hangeul);
int hangeul_to_mccune_reischauer(char *romaja, size_t, const char *hangeul);

/* Conversion to Hangeul (Hangeulization) */
int hangeulize(char *hangeul, size_t size, const char *romaja, RomanizationType rtype);
int hangeul_from_yale(char *hangeul, size_t, const char *romaja);
int hangeul_from_yale_original(char *hangeul, size_t, const char *romaja);
int hangeul_from_revised_romanization(char *hangeul, size_t, const char *romaja);
int hangeul_from_mccune_reischauer(char *hangeul, size_t, const char *romaja);

#endif
