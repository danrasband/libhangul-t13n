/**
 * Copyright (C) 2013 Daniel Rasband.
 *
 * This code has mostly been copied from the coreutils package:
 * Copyright (C) 1990-2000, 2002-2006, 2008-2011 Free Software Foundation, Inc.
 */

#include "xmalloc.h"

void xalloc_die(void);

void *
xmalloc (size_t n)
{
    void *p = malloc (n);
    if (!p && n != 0)
        xalloc_die ();
    return p;
}

void *
xrealloc (void *p, size_t n)
{
    if (!n && p) {
        free (p);
        return NULL;
    }

    p = realloc (p, n);
    if (!p && n)
        xalloc_die ();
    return p;
}

void
xalloc_die (void)
{
    fprintf (stderr, _("memory exhausted"));
    abort ();
}
