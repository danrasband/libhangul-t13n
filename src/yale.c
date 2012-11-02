/**
 * Copyright 2012 Daniel C. Rasband.
 */
#include "yale.h"

static const char choseong[][3] = {
    "k", "kk", "n", "t", "tt",
    "l", "m", "p", "pp", "s",
    "ss", "", "c", "cc", "ch",
    "kh", "th", "ph", "h"
};

static const char jungseong[][4] = {
    "a", "ay", "ya", "yay",
    "e", "ey", "ye", "yey",
    "o", "wa", "way", "oy", "yo",
    "wu", "we", "wey", "wi",
    "yu", "u", "ui", "i"
};

static const char jongseong[][4] = {
    "",
    "k", "kk", "ks",
    "n", "nc", "nh",
    "t",
    "l", "lk", "lm", "lp", "ls", "lth", "lph", "lh",
    "m",
    "p", "ps",
    "s", "ss",
    "ng",
    "c", "ch",
    "kh",
    "th",
    "ph",
    "h"
};

/* Build yale romaja from Hangeul */
int
_hangeul_to_yale(Romaja **yaleRef, const Hangeul *hangeul) {
    const Hangeul *ptr = hangeul;
    utf8char initial[4];
    utf8char vowel[4];
    utf8char final[4];
    utf8char nonhangeul;
    SyllableType syllable_type;

    while (ptr != NULL) {
        // romaja_push(yaleRef, )
        ptr = ptr->next;
    }

}
