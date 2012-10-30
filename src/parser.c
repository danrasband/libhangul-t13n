/**
 * Copyright 2012 Daniel C. Rasband.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "encoding.h"

bool
hangeul_parse_str(Hangeul** hangeulRef, size_t size, const char *source)
{
    bool success = false;
    int i = 0;
    int overflow;
    int length;
    ucschar current;

    ucschar choseong;
    ucschar jungseong;
    ucschar jongseong;
    ucschar nonhangeul;
    ucschar combined;

    SyllableType syllable_type;

    ucschar *ucs_str = NULL;

    ucs_str = malloc(strlen(source) * sizeof(ucschar) + sizeof(ucschar));

    overflow = utf8_to_ucs(ucs_str, strlen(source) * sizeof(ucschar), source);

    printf("overflow: %d\n", overflow);

    while (overflow > 0) {
        ucs_str = realloc(ucs_str, sizeof(ucs_str) + overflow);
        overflow = utf8_to_ucs(ucs_str, sizeof(ucs_str), source);
    }

    /* realloc down */
    /*ucs_str = realloc(ucs_str, ucs_strlen(ucs_str) * sizeof(ucs_str) + sizeof(ucschar));*/
    length = ucs_strlen(ucs_str);
    printf("ucs_str[0] in parser: %x\n", ucs_str[0]);
    printf("length: %d\n", length);
    for (i = 0; i < length; i++) {
        printf("ucs_str[%d]: %x\n", i, ucs_str[i]);
        current = ucs_str[i];
        if (ucs_is_hangeul(current)) {
            choseong = ucs_hangeul_choseong(current);
            jungseong = ucs_hangeul_jungseong(current);
            jongseong = ucs_hangeul_jongseong(current);
            combined = current;
            syllable_type = HANGEUL;
        }
        else {
            choseong = 0;
            jungseong = 0;
            jongseong = 0;
            combined = 0;
            syllable_type = NONHANGEUL;
        }
        hangeul_push(hangeulRef, choseong, jungseong, jongseong, nonhangeul, combined, syllable_type);
    }

    return success;
}

bool
romaja_parse_str(Romaja** sentenceRef, size_t size, const char *source)
{
    bool success = false;
    return success;
}

