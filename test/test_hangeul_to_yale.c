/**
 * Copyright 2012 Daniel C. Rasband
 */
#include <hangeul-romaja.h>
#include <string.h>
#include <stdio.h>

int
test_main()
{
    char *yale_str = NULL;
    size_t size = 0;

    char hangeul_str[4] = "아";

    size = strlen((char *)hangeul_str) * 2;
    yale_str = malloc(size);

    hangeul_to_yale(yale_str, size, hangeul_str);
    if (strlen(yale_str) > 0) {
        yale_str = realloc(yale_str, strlen(yale_str));
    }

    if (strcmp(yale_str, "a") == 0) {
        free(yale_str);
        return 0;
    }
    free(yale_str);
    return 1;
}

