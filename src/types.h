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

    /* Indexes */
    int choseong;
    int jungseong;
    int jongseong;

    /* The whole UCS character */
    ucschar combined;

    SyllableType syllable_type;

    Hangeul *next;
};

struct _Romaja {
    Romaja *prev;

    /* These "strings" could be McCune-Reischauer utf8 chars or IPA characters
       that don't exist in the ASCII charset. */
    char *initial;
    char *vowel;
    char *final;
    char *combined;

    SyllableType syllable_type;

    Romaja *next;
};

void hangeul_push(Hangeul **hangeulRef, int choseong, int jungseong, int jongseong, ucschar combined, SyllableType syllable_type);
void romaja_push(Romaja **romajaRef, char *initial, char *vowel, char *final, char *combined, SyllableType syllable_type);

size_t hangeul_len(const Hangeul *hangeul);
size_t romaja_len(const Romaja *romaja);

void hangeul_destroy(Hangeul **hangeulRef);
void romaja_destroy(Romaja **romajaRef);

size_t utf8_strlen(const utf8char *str);
size_t ucs_strlen(const ucschar *str);

#endif
