/**
 * Copyright 2012 Daniel C. Rasband
 */
#ifndef __hangeul_romaja_types_h__
#define __hangeul_romaja_types_h__

#include <inttypes.h>

typedef uint32_t ucschar;

/* Data structures */
typedef struct _Hangeul Hangeul;
typedef struct _Romaja Romaja;

/* The type of syllable - hangeul or non-hangeul. */
typedef enum SyllableType {
    HANGEUL, NONHANGEUL
} SyllableType;

struct _Hangeul {
    Hangeul *prev;

    ucschar choseong;
    ucschar jungseong;
    ucschar jongseong;
    ucschar nonhangeul;
    ucschar combined;
    SyllableType syllable_type;

    Hangeul *next;
};

struct _Romaja {
    Romaja *prev;

    ucschar initial[4];
    ucschar vowel[4];
    ucschar final[4];
    ucschar nonhangeul;
    ucschar combined;
    SyllableType syllable_type;

    Romaja *next;
};

#endif
