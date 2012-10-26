/**
 * Copyright 2012 Daniel C. Rasband.
 */
#include "yale.h"

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
