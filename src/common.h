
#ifndef __COMMON_H__
#define __COMMON_H__

#include "../config.h"

#if HAVE_LIBINTL_H
#include <libintl.h>
#define _(msg) gettext(msg)
#else
#define _(msg) msg
#endif

#endif
