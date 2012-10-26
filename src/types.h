/**
 * Copyright 2012 Daniel C. Rasband
 */
#ifndef __hangeul_romaja_types_h__
#define __hangeul_romaja_types_h__

#include <stdint.h>
#include <stdio.h>

typedef uint8_t utf8char;
static const utf8char UTF8EOF = (uint8_t)EOF;

/* Data structures */
typedef struct _Hangeul Hangeul;
typedef struct _Romaja Romaja;

/* The type of syllable - hangeul or non-hangeul. */
typedef enum SyllableType {
    HANGEUL, NONHANGEUL
} SyllableType;

struct _Hangeul {
    Hangeul *prev;

    utf8char choseong[4];
    utf8char jungseong[4];
    utf8char jongseong[4];
    utf8char nonhangeul[7];
    utf8char combined[7];
    SyllableType syllable_type;

    Hangeul *next;
};

struct _Romaja {
    Romaja *prev;

    utf8char initial[4];
    utf8char vowel[4];
    utf8char final[4];
    utf8char nonhangeul;
    utf8char combined;
    SyllableType syllable_type;

    Romaja *next;
};

#endif
