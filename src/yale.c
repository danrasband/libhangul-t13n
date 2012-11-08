/**
 * Copyright 2012 Daniel C. Rasband.
 */
#include "yale.h"
#include <string.h>
#include <assert.h>

static const char initial[][3] = {
    "k", "kk", "n", "t", "tt",
    "l", "m", "p", "pp", "s",
    "ss", "", "c", "cc", "ch",
    "kh", "th", "ph", "h"
};

static const char vowel[][4] = {
    "a", "ay", "ya", "yay",
    "e", "ey", "ye", "yey",
    "o", "wa", "way", "oy", "yo",
    "wu", "we", "wey", "wi",
    "yu", "u", "ui", "i"
};

static const char final[][4] = {
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

/**
 * Build yale romaja from Hangeul
 *
 * This is the easiest romanization process and involves only a direct
 * correlation between the Korean syllable part and the roman equivalent.
 */
int
_hangeul_to_yale(Romaja **yaleRef, const Hangeul *hangeul) {
    const Hangeul *current = hangeul;

    char combined[12];

    int size = 0;

    while (current != NULL) {
        if (current->syllable_type == HANGEUL) {

            assert(strlen(initial[current->choseong]) <= 2);
            assert(strlen(initial[current->jungseong]) <= 3);
            assert(strlen(initial[current->jongseong]) <= 3);

            strncat(combined, initial[current->choseong], strlen(initial[current->choseong]) + 1);
            strncat(combined, vowel[current->jungseong], strlen(initial[current->jungseong]) + 1);
            strncat(combined, final[current->jongseong], strlen(initial[current->jongseong]) + 1);

            romaja_push(yaleRef, (char *)initial[current->choseong], (char *)vowel[current->jungseong], (char *)final[current->jongseong], combined, current->syllable_type);
        }
        else {
            ucs_to_utf8(combined, &(current->combined), sizeof(current->combined));
            romaja_push(yaleRef, NULL, NULL, NULL, combined, current->syllable_type);

        }

        memset(combined, 0, sizeof(combined));

        current = current->next;
        size++;
    }

    return size;
}
