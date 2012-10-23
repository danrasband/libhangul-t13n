/**
 * Copyright 2012 Daniel C. Rasband
 */
#ifndef __hangeul_romaja_h__
#define __hangeul_romaja_h__

#include <stdlib.h>

typedef uint32_t ucschar;

/* Data structures */
typedef struct _HangeulSentence HangeulSentence;
typedef struct _RomajaSentence RomajaSentence;

/* Conversion from Hangeul */
void hangeul_to_yale(RomajaSentence **convertedSentenceRef, const HangeulSentence *sentence);
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

/* Utility Functions */
/*void parse_hangeul_string(HangeulSentence **sentenceRef, const char *source);
void parse_romaja_string(RomajaSentence **sentenceRef, const char *source);
char *hangeul_to_string(const HangeulSentence *sentence);
char *romaja_to_string(const RomajaSentence *sentence);*/
int hangeul_strlen(HangeulSentence *sentence);
int romaja_strlen(RomajaSentence *sentence);
void hangeul_sentence_push(HangeulSentence **sentence, ucschar combined);
void romaja_sentence_push(RomajaSentence **sentence, ucschar character);


#endif
