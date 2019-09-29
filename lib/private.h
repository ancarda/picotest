//
// PicoTest private variables and macros.
//
// PLEASE DO NOT USE THESE IN YOUR TESTS OR CODE
// You may break the tests. Everything here is not part of the API scope and
// is subject to change without notice between versions.
//

#pragma once

#include <stdbool.h>

int __tests_run            = 0;
int __assertions_attempted = 0;
int __assertions_succeeded = 0;

#define __COLOR_FG_GREEN  "\x1B[32m"
#define __COLOR_BG_GREEN  "\x1B[42m"
#define __COLOR_FG_YELLOW "\x1B[33;1m"
#define __COLOR_BG_YELLOW "\x1B[103m"
#define __COLOR_BG_RED    "\x1B[101m"
#define __COLOR_RESET     "\x1B[0m"

#define __ERR_MARKER "\n  \x1B[37;1m\x1B[41m ERR \x1B[0m "

#define __EXPAND(x) #x

#define __TEST_EMPTY \
    printf(" %s%s%s\n", __COLOR_BG_YELLOW, " No Assertions Made ", __COLOR_RESET);

#define __TEST_PASSED \
    printf(" %s%s%s\n", __COLOR_BG_GREEN, " OK ", __COLOR_RESET); \
    return EXIT_SUCCESS;

#define __TRY_ASSERT(block) \
    __assertions_attempted++; \
    block \
    __assertions_succeeded++;

#define __ASSERTION_FAILED \
    puts(""); \
    return EXIT_FAILURE;
