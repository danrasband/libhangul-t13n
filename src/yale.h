/**
 * Copyright 2012 Daniel C. Rasband.
 */
#ifndef __yale_h__
#define __yale_h__

/* Includes */
#include "types.h"
#include "hangeul-romaja.h"

/* Build yale romaja from Hangeul */
int _hangeul_to_yale(Romaja **yaleRef, const Hangeul *hangeul);

#endif
