/**
 * Copyright 2012 Daniel C. Rasband.
 */
#include "yale.h"

/* Build yale romaja from Hangeul */
int
_hangeul_to_yale(Romaja **yaleRef, const Hangeul *hangeul) {
    const Hangeul *ptr = hangeul;
    ucschar initial[4];
    ucschar vowel[4];
    ucschar final[4];
    ucschar nonhangeul;
    SyllableType syllable_type;

    while (ptr != NULL) {
        // romaja_push(yaleRef, )
        ptr = hangeul->next;
    }

}
