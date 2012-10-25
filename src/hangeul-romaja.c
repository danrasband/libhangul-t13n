/**
 * Copyright 2012 Daniel C. Rasband.
 */
#include "hangeul-romaja.h"
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

typedef uint32_t ucschar;

/* Data structures */
typedef struct _Hangeul Hangeul;
typedef struct _Romaja Romaja;

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

/* Declarations */
int hangeul_parse_str(Hangeul **hangeulRef, const char *source);
int hangeul_puts(const Hangeul* hangeul);
int hangeul_snprint(char *dest, size_t size, const Hangeul* hangeul);
int hangeul_strlen(const Hangeul *hangeul);
int romaja_parse_str(Romaja **romajaRef, const char *source);
int romaja_strlen(const Romaja *romaja);
void hangeul_push(Hangeul **hangeul, ucschar combined);
void romaja_push(Romaja **romaja, ucschar character);

/* Build yale romaja from Hangeul */
int
_hangeul_to_yale(Romaja **yaleRef, const Hangeul *hangeul) {
    const Hangeul *ptr = hangeul;

    while (ptr != NULL) {
        ptr = hangeul->next;
    }

}

int
hangeul_to_yale(char *yale, size_t size, const char *hangeul)
{
    int chars_left = 0;
    Hangeul *h = NULL;
    Romaja *r = NULL;

    /* Parse hangeul string into manageable chunks */
    hangeul_parse_str(&h, hangeul);

    /* Convert to yale in manageable chunks */
    _hangeul_to_yale(&r, h);

    /* Copy string to yale var */
    chars_left = romaja_snprint(yale, size, r);

    /*hangeul_destroy(h);
    romaja_destroy(r);*/

    return chars_left;
}

int
hangeul_parse_str(Hangeul** hangeulRef, const char *source)
{
    int success = 0;
    int i = 0;
    char next = source[i];
    char hangeul[3];

    while ((next = source[i]) != '\0') {
        i++;
    }

    return success;
}

int
romaja_parse_str(Romaja** sentenceRef, const char *source)
{
    int success = 0;
    return success;
}

int
hangeul_puts(const Hangeul* sentence)
{
    int success = 0;
    return success;
}

int
hangeul_snprint(char *dest, size_t size, const Hangeul* sentence)
{
    int chars_not_printed = 0;
    return chars_not_printed;
}

int
romaja_puts(const Romaja* sentence)
{
    int success = 0;
    char out[romaja_strlen(sentence) + 1];
    romaja_snprint(out, sizeof(out), sentence);
    success = puts(out);
    return success;
}

int
romaja_snprint(char *dest, size_t size, const Romaja* romaja)
{
    if (size == 0) {
        return romaja_strlen(romaja);
    }

    return romaja_strlen(romaja) - strlen(dest);
}

int
hangeul_strlen(const Hangeul* hangeul)
{
    return 0;
}

int
romaja_strlen(const Romaja *romaja)
{
    int len = 0;
    Romaja *current = malloc(sizeof(Romaja));
    // *current = *romaja;

    /*while (current != NULL) {
        if (current->syllable_type == HANGEUL) {
            if (current->initial != NULL) {
                len += sizeof(current->initial);
            }
            if (current->vowel != NULL) {
                len += sizeof(current->vowel);
            }
            if (current->final != NULL) {
                len += sizeof(current->final);
            }
        }
        else {
            if (current->nonhangeul) {
                len += sizeof(current->nonhangeul);
            }
        }
        current = sentence->next;
    }*/

    romaja_destroy(current);

    return len;
}

void
hangeul_push(Hangeul **hangeul, ucschar combined)
{
    /* Parse combined character into nonhangeul or choseong, jungseong,
    jongseong */

}

void
romaja_push(Romaja **romaja, ucschar character)
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

ucschar
_hangeul_get_choseong(ucschar combined)
{

}

ucschar
_hangeul_get_jungseong(ucschar combined)
{

}

ucschar
_hangeul_get_jongseong(ucschar combined)
{

}

