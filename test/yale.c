/**
 * Copyright 2012 Daniel C. Rasband
 */
#include <stdio.h>
#include <hangeul-romaja.h>

int
test_hangeul_to_yale()
{
    return 0;
}

int
test_yale_to_hangeul()
{
    int result = testme();
    if (result != 0) {
        return 1;
    }
    return 0;
}

int
main()
{
    int result1 = test_hangeul_to_yale();
    int result2 = test_yale_to_hangeul();
    printf("Result1: %d\nResult2: %d\n", result1, result2);
    return 0;
}

