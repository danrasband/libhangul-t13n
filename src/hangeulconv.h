/**
 * Header file for hangeulconv.c.
 */

#ifndef __HANGEULCONV_H__

#if HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef EXIT_SUCCESS
  #define EXIT_SUCCESS 0
#endif

#ifndef HANGEULCONV_FAILURE
  #define HANGEULCONV_FAILURE 2
#endif

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <libintl.h>

/* Local includes */
#include "progname.h"
#include "libhangeul-romaja.h"

#define _(msgid) gettext(msgid)

#endif

