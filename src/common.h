
#ifndef __COMMON_H__
#define __COMMON_H__

#include "../config.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* I18n */
#include <libintl.h>
#define _(msg) gettext(msg)

/* Size of array */
#define NARRAY(ary) sizeof(ary)/sizeof(ary[0])

#endif
