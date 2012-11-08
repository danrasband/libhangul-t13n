/**
 * Copyright 2012 Daniel C. Rasband
 */
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "types.h"

void
hangeul_push(Hangeul **hangeulRef, int choseong, int jungseong, int jongseong, ucschar combined, SyllableType syllable_type)
{
    /* Parse combined character into nonhangeul or choseong, jungseong,
    jongseong */
    Hangeul *newHangeul = malloc(sizeof *newHangeul);

    newHangeul->choseong = choseong;
    newHangeul->jungseong = jungseong;
    newHangeul->jongseong = jongseong;
    newHangeul->combined = combined;
    newHangeul->syllable_type = syllable_type;

    newHangeul->next = (*hangeulRef);
    (*hangeulRef) = newHangeul;
}

void
romaja_push(Romaja **romajaRef, char *initial, char *vowel, char *final, char *combined, SyllableType syllable_type)
{
    /* Add to most recent syllable or create new syllable to add to. */
    Romaja *newRomaja = malloc(sizeof *newRomaja);

    if (syllable_type == HANGEUL) {
        assert(initial != NULL && vowel != NULL && final != NULL);

        newRomaja->initial = malloc((strlen(initial) + 1) * sizeof(*(newRomaja->initial)));
        strncpy(newRomaja->initial, initial, (strlen(final) + 1) * sizeof(*(newRomaja->final)));

        newRomaja->vowel = malloc((strlen(vowel) + 1) * sizeof(*(newRomaja->vowel)));
        strncpy(newRomaja->vowel, vowel, (strlen(final) + 1) * sizeof(*(newRomaja->final)));

        newRomaja->final = malloc((strlen(final) + 1) * sizeof(*(newRomaja->final)));
        strncpy(newRomaja->final, final, (strlen(final) + 1) * sizeof(*(newRomaja->final)));
    }

    newRomaja->combined = malloc((strlen(combined) + 1) * sizeof(*(newRomaja->combined)));
    strncpy(newRomaja->combined, combined, (strlen(combined) + 1) * sizeof(*(newRomaja->combined)));

    newRomaja->syllable_type = syllable_type;

    newRomaja->next = (*romajaRef);
    (*romajaRef) = newRomaja;
}

size_t
hangeul_len(const Hangeul *hangeul)
{
    size_t len = 0;
    const Hangeul *current = hangeul;

    while (current != NULL) {
        len++;
        current = current->next;
    }

    return len;
}

size_t
romaja_len(const Romaja *romaja)
{
    size_t len = 0;
    const Romaja *current = romaja;

    while (current != NULL) {
        len++;
        current = current->next;
    }

    return len;
}

void
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

void
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
