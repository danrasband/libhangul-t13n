/**
 * Copyright 2012 Daniel C. Rasband
 */
#include <hangeul-romaja.h>
#include <string.h>
#include <stdio.h>

int
test_main()
{
    int exit_code = 1;
    char *yale_str = NULL;
    size_t size = 0;

    char hangeul_str[33] = "아버지, 돌이 굴러와유!~";

    yale_str = NULL;

    size = hangeul_to_yale(yale_str, hangeul_str, size);
    printf("estimated size: %lu\n", size);

    yale_str = malloc((size + 1) * sizeof *yale_str);
    hangeul_to_yale(yale_str, hangeul_str, (size + 1) * sizeof *yale_str);

    printf("'%s'\n", yale_str);

    if (strcmp(yale_str, "apeci, toli kwullewayu!~") == 0) {
        exit_code = 0;
    }

    free(yale_str);
    return exit_code;
}

