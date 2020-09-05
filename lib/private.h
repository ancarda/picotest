/* SPDX-License-Identifier: AGPL-3.0-or-later */

/**
 * PicoTest private variables and macros.
 *
 * PLEASE DO NOT USE THESE IN YOUR TESTS OR CODE
 * You may break the tests. Everything here is not part of the API scope and
 * is subject to change without notice between versions.
 */

#ifndef PICOTEST_PRIVATE_H
#define PICOTEST_PRIVATE_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int __tests_run = 0;
int __tests_run_in_suite = 0;
bool __in_test_suite = false;
int __assertions_attempted = 0;
int __assertions_succeeded = 0;

struct timespec __tests_began;
struct timespec __tests_concluded;

#define __COLOR_FG_GREEN "\x1B[32m"
#define __COLOR_BG_GREEN "\x1B[42m"
#define __COLOR_FG_YELLOW "\x1B[33;1m"
#define __COLOR_BG_YELLOW "\x1B[103m"
#define __COLOR_BG_RED "\x1B[101m"
#define __COLOR_RESET "\x1B[0m"

#define __ERR_MARKER "\n    \x1B[37;1m\x1B[41m ERR \x1B[0m "

#define __EXPAND(x) #x

#define __TEST_EMPTY                                                           \
    do                                                                         \
    {                                                                          \
        printf(" %s%s%s\n", __COLOR_BG_YELLOW, " No Assertions Made ",         \
               __COLOR_RESET);                                                 \
        return EXIT_SUCCESS; /* Assume success since it's a warning */         \
    } while (0)

#define __TEST_PASSED                                                          \
    do                                                                         \
    {                                                                          \
        printf(" %s%s%s\n", __COLOR_BG_GREEN, " OK ", __COLOR_RESET);          \
        return EXIT_SUCCESS;                                                   \
    } while (0)

#define __SUITE_EMPTY                                                          \
    do                                                                         \
    {                                                                          \
        printf("  %s%s%s\n", __COLOR_BG_YELLOW, " No Tests Run ",              \
               __COLOR_RESET);                                                 \
        puts("  => Did you include a RUN_TEST(test_name); call before "        \
             "END_TEST_SUITE;");                                               \
    } while (0)

#define __CHECK_NOT_IN_TEST_SUITE                                              \
    do                                                                         \
    {                                                                          \
        if (__in_test_suite)                                                   \
        {                                                                      \
            printf("%s%s%s", __COLOR_BG_YELLOW, " Test Suite Not Closed ",     \
                   __COLOR_RESET);                                             \
            puts(" -- Call END_TEST_SUITE; before CONCLUDE_TESTING or "        \
                 "BEGIN_TEST_SUITE!");                                         \
        }                                                                      \
    } while (0)

#define __TRY_ASSERT(block)                                                    \
    do                                                                         \
    {                                                                          \
        __assertions_attempted++;                                              \
        block __assertions_succeeded++;                                        \
    } while (0)

#define __ASSERTION_FAILED                                                     \
    do                                                                         \
    {                                                                          \
        puts("");                                                              \
        return EXIT_FAILURE;                                                   \
    } while (0)

char* __str_replace_byte(const char* str, const char find, const char replace)
{
    char* out;
    int i;

    assert(str != NULL);
    assert(find != replace);

    out = malloc(sizeof(char) * strlen(str) + 1);
    assert(out != NULL);

    for (i = 0; i < (int) strlen(str); i++)
    {
        if (str[i] == find)
        {
            out[i] = replace;
        }
        else
        {
            out[i] = str[i];
        }
    }

    /* Include a null terminate byte */
    out[i] = '\0';

    return out;
}

#endif /* PICOTEST_PRIVATE_H */
