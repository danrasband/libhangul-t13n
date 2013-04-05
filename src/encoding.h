
#ifndef __UTF8_H__
#define __UTF8_H__

#include <iconv.h>
#include <errno.h>
#include "common.h"

char *encode(char *orig, char *to_code, char *from_code);

#endif
