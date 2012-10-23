/**
 * Copyright 2012 Daniel C. Rasband.
 */
#include "hangeul-romaja.h"
#include <inttypes.h>

typedef enum SyllableType {
    HANGEUL, NONHANGEUL
} SyllableType;

struct _HangeulSentence {
    HangeulSentence *prev;

    ucschar choseong;
    ucschar jungseong;
    ucschar jongseong;
    ucschar nonhangeul;
    ucschar combined;
    SyllableType syllable_type;

    HangeulSentence *next;
};

struct _RomajaSentence {
    RomajaSentence *prev;

    ucschar initial[4];
    ucschar vowel[4];
    ucschar final[4];
    ucschar nonhangeul;
    ucschar combined;
    SyllableType syllable_type;

    RomajaSentence *next;
};

void
hangeul_to_yale(RomajaSentence **convertedSentenceRef, const HangeulSentence *sentence)
{

}

void
_hangeul_to_yale(RomajaSentence **sentenceRef, const HangeulSentence* sentence)
{

}

void
hangeul_parse_string(HangeulSentence** sentenceRef, const char *source)
{

}

void
romaja_parse_string(RomajaSentence** sentenceRef, const char *source)
{

}

char *
hangeul_to_string(const HangeulSentence *sentence)
{

}

char *
romaja_to_string(const RomajaSentence *sentence)
{

}

void
print_hangeul_sentence(const HangeulSentence* sentence)
{

}

void
print_romaja_sentence(const RomajaSentence* sentence)
{

}

int
hangeul_strlen(HangeulSentence* sentence)
{
    return 0;
}

int
romaja_strlen(RomajaSentence* sentence)
{
    int len = 0;
    RomajaSentence *current = sentence;

    while (current != NULL) {
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
    }

    return len;
}

void
hangeul_sentence_push(HangeulSentence **sentence, ucschar combined)
{
    /* Parse combined character into nonhangeul or choseong, jungseong,
    jongseong */
}

void romaja_sentence_push(RomajaSentence **sentence, ucschar character)
{
    /* Add to most recent syllable or create new syllable to add to. */
}
