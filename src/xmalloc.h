
#ifndef __XMALLOC_H__
#define __XMALLOC_H__

#include "common.h"

void *xmalloc(size_t n);
void *xrealloc(void *p, size_t n);

#endif
