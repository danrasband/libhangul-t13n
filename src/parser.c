/**
 * Copyright 2012 Daniel C. Rasband.
 */
#include "parser.h"
#include <string.h>

#define UTF8_ASCII_LOW 0x0000
#define UTF8_ASCII_HIGH 0x007f
#define UTF8_TWOBYTE_LOW 0x0080
#define UTF8_TWOBYTE_HIGH 0x07ff
#define UTF8_THREEBYTE_LOW 0x0800
#define UTF8_THREEBYTE_HIGH 0xffff
#define UTF8_FOURBYTE_LOW 0x010000
#define UTF8_FOURBYTE_HIGH 0x1fffff
#define UTF8_FIVEBYTE_LOW 0x200000
#define UTF8_FIVEBYTE_HIGH 0x03ffffff
#define UTF8_SIXBYTE_LOW 0x04000000
#define UTF8_SIXBYTE_HIGH 0x7fffffff

#define UTF8_SUBBYTE_MASK   0b10000000
#define UTF8_ONEBYTE_MASK   0b00000000
#define UTF8_TWOBYTE_MASK   0b11000000
#define UTF8_THREEBYTE_MASK 0b11100000
#define UTF8_FOURBYTE_MASK  0b11110000
#define UTF8_FIVEBYTE_MASK  0b11111000
#define UTF8_SIXBYTE_MASK   0b11111100

int
hangeul_parse_str(Hangeul** hangeulRef, size_t size, const char *source)
{
    int success = 0;
    int i = 0;
    utf8char choseong[4] = {0xe3, 0x84, 0xb1};
    utf8char jungseong[4] = {0xe3, 0x85, 0x8f};
    utf8char jongseong[4];
    utf8char nonhangeul[7];
    utf8char combined[7] = {0xea, 0xb0, 0x80};
    SyllableType syllable_type;

    utf8char c;
    utf8char hangeul_char[3];

    while ((c = source[i]) != UTF8EOF && (i < size || size == 0)) {
        syllable_type = HANGEUL;

        hangeul_push(hangeulRef, choseong, jungseong, jongseong, nonhangeul, combined, syllable_type);
        i++;
    }

    return success;
}

int
romaja_parse_str(Romaja** sentenceRef, size_t size, const char *source)
{
    int success = 0;
    return success;
}
