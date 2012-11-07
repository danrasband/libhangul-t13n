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

    char hangeul_str[33] = "아버지, 돌이 굴러와유!~";

    yale_str = malloc((strlen(hangeul_str) * 2 + 1) * sizeof *yale_str);

    hangeul_to_yale(yale_str, size, hangeul_str);

    if (strlen(yale_str) > 0) {
        yale_str = realloc(yale_str, (strlen(yale_str) + 1) * sizeof *yale_str);
    }

    printf("'%s'\n", yale_str);

    if (strcmp(yale_str, "apeci, toli kwullewayu!~") == 0) {
        free(yale_str);
        return 0;
    }

    free(yale_str);
    return 1;
}

