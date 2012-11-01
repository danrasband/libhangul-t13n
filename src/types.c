/**
 * Copyright 2012 Daniel C. Rasband
 */
#include <stdlib.h>
#include <string.h>
#include "types.h"

void
hangeul_push(Hangeul **hangeulRef, ucschar choseong, ucschar jungseong, ucschar jongseong, ucschar nonhangeul, ucschar combined, SyllableType syllable_type)
{
    /* Parse combined character into nonhangeul or choseong, jungseong,
    jongseong */
    Hangeul *newHangeul = (Hangeul *)malloc(sizeof(Hangeul));

    newHangeul->choseong = choseong;
    newHangeul->jungseong = jungseong;
    newHangeul->jongseong = jongseong;
    newHangeul->nonhangeul = nonhangeul;
    newHangeul->combined = combined;
    newHangeul->syllable_type = syllable_type;

    newHangeul->next = *hangeulRef;
    (*hangeulRef) = newHangeul;
}

void
romaja_push(Romaja **romajaRef, ucschar initial[4], ucschar vowel[4], ucschar final[4], ucschar nonhangeul, ucschar combined[8], SyllableType syllable_type)
{
    /* Add to most recent syllable or create new syllable to add to. */

}

int
hangeul_destroy(Hangeul **hangeulRef)
{
    Hangeul *current = *hangeulRef;
    Hangeul *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *hangeulRef = NULL;
}

int
romaja_destroy(Romaja **romajaRef)
{
    Romaja *current = *romajaRef;
    Romaja *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *romajaRef = NULL;
}


/* The string length of utf8chars */
size_t
utf8_strlen(const utf8char *str)
{
    return (size_t)(strlen((char *)str) / sizeof(utf8char));
}

/* The string length of ucschars */
size_t
ucs_strlen(const ucschar *str)
{
    int i = 0;
    size_t len = 0;
    ucschar current;

    while ((current = str[i++]) != (ucschar)'\0') {
        len++;
    }

    return len;
}
