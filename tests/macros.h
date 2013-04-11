/**
 * Copyright (C) 2013 Daniel Rasband.
 */

#ifndef __MACROS_H__
#define __MACROS_H__

#include <stdio.h>

#define PASS 0
#define FAIL 1
#define SKIP 77

#ifndef ASSERT
#define ASSERT(tf) if (!tf) {\
    fprintf (stderr, "Failure at line %d in file %s:\n", __LINE__, __FILE__); \
    exit (FAIL); \
}
#endif

#endif

