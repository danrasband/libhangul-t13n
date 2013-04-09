/**
 *
 */

#include "../src/encoding.h"
#include <stdio.h>
#include <string.h>

#define PASS 0
#define FAIL 1

int
main()
{
    char *from_encoding = "EUC-KR";
    char *to_encoding = "UTF-8";

    // Orig is euc-kr-encoded "안녕\n"
    char orig[] = {0xbe, 0xc8, 0xb3, 0xe7, 0x0a, '\0'};
    char *encoded;
    int pass = FAIL;
    encoded = encode(orig, to_encoding, from_encoding);

    if (0 == strncmp("안녕\n", encoded, strlen("안녕\n")))
        pass = PASS;

    free(encoded);
    return pass;
}

