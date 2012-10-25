/**
 * Copyright 2012 Daniel C. Rasband
 */
#ifndef __hangeul_romaja_h__
#define __hangeul_romaja_h__

#include <stdlib.h>

/* Conversion from Hangeul */
int hangeul_to_yale(char *yale, size_t size, const char *hangeul);
/*
void hangeul_to_yale_original();
void hangeul_to_revised();
void hangeul_to_mccune_reischauer();
*/

/* Conversion to Hangeul */
/*
void hangeul_from_yale();
void hangeul_from_yale_original();
void hangeul_from_revised_romanization();
void hangeul_from_mccune_reischauer();
*/


#endif
