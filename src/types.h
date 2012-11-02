/**
 * Copyright 2012 Daniel C. Rasband
 */
#ifndef __hangeul_romaja_types_h__
#define __hangeul_romaja_types_h__

#include <stdint.h>
#include <stdio.h>

typedef uint8_t utf8char;
typedef uint32_t ucschar;
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

    int choseong;
    int jungseong;
    int jongseong;
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
    ucschar combined[8];

    SyllableType syllable_type;

    Romaja *next;
};

void hangeul_push(Hangeul **hangeulRef, ucschar choseong, ucschar jungseong, ucschar jongseong, ucschar nonhangeul, ucschar combined, SyllableType syllable_type);
void romaja_push(Romaja **romajaRef, ucschar initial[4], ucschar vowel[4], ucschar final[4], ucschar nonhangeul, ucschar combined[8], SyllableType syllable_type);

int hangeul_destroy(Hangeul **hangeulRef);
int romaja_destroy(Romaja **romajaRef);

size_t utf8_strlen(const utf8char *str);
size_t ucs_strlen(const ucschar *str);

#endif
