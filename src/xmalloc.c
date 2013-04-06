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
