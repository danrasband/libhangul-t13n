/**
 * Copyright 2012 Daniel C. Rasband
 */
#include <hangeul-romaja.h>

void
build_test_romaja_sentence(RomajaSentence **sentenceRef)
{

}

void
build_test_hangeul_sentence(HangeulSentence **sentenceRef, int length)
{
	int i;
	HangeulSentence *tmp = *sentenceRef;

	for (i = 0; i < length; i++) {
		hangeul_sentence_push(&(*sentenceRef), );
	}
}
