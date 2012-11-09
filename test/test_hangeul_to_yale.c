/**
 * Copyright 2012 Daniel C. Rasband
 */
#include <hangeul-romaja.h>
#include <string.h>
#include <stdio.h>

#define YALE_MAX_TEST_STR_LEN 100

static const char test_strings[][YALE_MAX_TEST_STR_LEN] = {
    /* Initials */
    "가 까 나 다 따 라 마 바 빠 사 싸 아 자 짜 차 카 타 파 하",
    /* Vowels */
    "가 개 갸 걔 거 게 겨 계 고 과 괘 괴 교 구 궈 궤 귀 규 그 긔 기",
    /* Finals (Group 1) */
    "나 낙 낚 낛 난 낝 낞 낟 날 낡 낢 낣 낤 낥",
    /* Finals (Group 2) */
    "낦 낧 남 납 낪 낫 났 낭 낮 낯 낰 낱 낲 낳"
};

static const char romanized_strings[][YALE_MAX_TEST_STR_LEN] = {
    /* Initials */
    "ka kka na ta tta la ma pa ppa sa ssa a ca cca cha kha tha pha ha",
    /* Vowels */
    "ka kay kya kyay ke key kye kyey ko kwa kway koy kyo kwu kwe kwey kwi kyu ku kui ki",
    /* Finals (Group 1) */
    "na nak nakk naks nan nanc nanh nat nal nalk nalm nalp nals nalth",
    /* Finals (Group 2) */
    "nalph nalh nam nap naps nas nass nang nac nach nakh nath naph nah"
};

int
test_main()
{
    int i, exit_code = 0;
    char *yale_str = NULL;
    size_t size = 0;

    char hangeul_str[YALE_MAX_TEST_STR_LEN];

    for (i = 0; i < sizeof(test_strings) / YALE_MAX_TEST_STR_LEN; i++) {
        strncpy(hangeul_str, test_strings[i], 99);
        size = hangeul_to_yale(yale_str, hangeul_str, size);
        /*printf("calculated size: %lu\n", size);*/

        yale_str = malloc((size + 1) * sizeof *yale_str);
        hangeul_to_yale(yale_str, hangeul_str, (size + 1) * sizeof *yale_str);

        /*printf("%s\n", yale_str);*/

        if (strcmp(yale_str, romanized_strings[i]) != 0) {
            exit_code = 1;
            /*printf("Exiting:\n%s\n%s\n", yale_str, romanized_strings[i]);*/
            free(yale_str);
            break;
        }

        memset(hangeul_str, 0, 100);
        size = 0;
        free(yale_str);
    }

    return exit_code;
}

