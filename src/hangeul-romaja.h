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
size_t romanize(char *romaja, const char *hangeul, RomanizationType rtype, size_t size);
size_t hangeul_to_yale(char *romaja, const char *hangeul, size_t size);
size_t hangeul_to_yale_original(char *romaja, const char *hangeul, size_t size);
size_t hangeul_to_revised(char *romaja, const char *hangeul, size_t size);
size_t hangeul_to_mccune_reischauer(char *romaja, const char *hangeul, size_t size);

/* Conversion to Hangeul (Hangeulization) */
size_t hangeulize(char *hangeul, const char *romaja, RomanizationType rtype, size_t size);
size_t hangeul_from_yale(char *hangeul, const char *romaja, size_t size);
size_t hangeul_from_yale_original(char *hangeul, const char *romaja, size_t size);
size_t hangeul_from_revised_romanization(char *hangeul, const char *romaja, size_t size);
size_t hangeul_from_mccune_reischauer(char *hangeul, const char *romaja, size_t size);

#endif
