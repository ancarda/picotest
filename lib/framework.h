/**
 * PicoTest Framework
 *
 * You should include this file, and only this file, for normal usage.
 * Do not include assertions.h
 */

#ifndef PICOTEST_FRAMEWORK_H
#define PICOTEST_FRAMEWORK_H

#include "assertions.h"
#include "private.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Initialize PicoTest
 *
 * This should be at the very start of main, and run before any test suite or
 * tests.
 */
#define BEGIN_TESTING                                                          \
    do                                                                         \
    {                                                                          \
        puts("PicoTest");                                                      \
        puts("========");                                                      \
        puts("");                                                              \
        clock_gettime(CLOCK_MONOTONIC, &__tests_began);                        \
    } while (0)

/**
 * Begins a test suite; a collection of tests.
 */
#define BEGIN_TEST_SUITE(suite_name)                                           \
    do                                                                         \
    {                                                                          \
        __CHECK_NOT_IN_TEST_SUITE;                                             \
        __in_test_suite = true;                                                \
        printf("%s:\n", __EXPAND(suite_name));                                 \
    } while (0)

/**
 * Defines a new test. Provide the test name, and a body (use curly braces).
 * The body should contain one or more ASSERT_xxx calls.
 *
 * The test name should have underscores rather than spaces since it will
 * become a C function. Underscores will be replaced with spaces when the test
 * name is printed.
 */
#define IT_SHOULD(test_name, test_body)                                        \
    int it_should_##test_name()                                                \
    {                                                                          \
        char* __formatted_name =                                               \
            __str_replace_byte(__EXPAND(test_name), '_', ' ');                 \
        printf("  it should %s:", __formatted_name);                           \
        free(__formatted_name);                                                \
        int __assertions_before_this_test = __assertions_attempted;            \
        test_body if (__assertions_before_this_test == __assertions_attempted) \
        {                                                                      \
            __TEST_EMPTY;                                                      \
        }                                                                      \
        __TEST_PASSED;                                                         \
    }

/**
 * Execute a previously defined test.
 *
 * This should be used after BEGIN_TESTING in main(). The name is the same as
 * you provided to IT_SHOULD, complete with underscores if present.
 */
#define RUN_TEST(test_name)                                                    \
    do                                                                         \
    {                                                                          \
        it_should_##test_name();                                               \
        __tests_run++;                                                         \
        __tests_run_in_suite++;                                                \
    } while (0)

/**
 * End a test suite.
 *
 * To be called after BEGIN_TEST_SUITE and 1 or more RUN_TEST calls.
 */
#define END_TEST_SUITE                                                         \
    do                                                                         \
    {                                                                          \
        __in_test_suite = false;                                               \
        if (__tests_run_in_suite == 0)                                         \
        {                                                                      \
            __SUITE_EMPTY;                                                     \
        }                                                                      \
        puts("");                                                              \
        __tests_run_in_suite = 0;                                              \
    } while (0)

/**
 * Print an overall score and return an exit value for CI systems.
 *
 * To be used after all RUN_TEST calls in main().
 *
 * Exit value is given via `return` so this macro call should be in `main()`,
 * or the value should be captured and then returned from main.
 */
#define CONCLUDE_TESTING                                                       \
    do                                                                         \
    {                                                                          \
        clock_gettime(CLOCK_MONOTONIC, &__tests_concluded);                    \
        float __runtime_s =                                                    \
            ((float) __tests_concluded.tv_sec - __tests_began.tv_sec);         \
        float __runtime_ns =                                                   \
            (__tests_concluded.tv_nsec - __tests_began.tv_nsec);               \
        float __runtime =                                                      \
            ((__runtime_s * 1000000000) + __runtime_ns) / 1000000000;          \
        puts("");                                                              \
        assert(__assertions_attempted >= __assertions_succeeded);              \
        assert(__assertions_attempted >= 0);                                   \
        assert(__assertions_succeeded >= 0);                                   \
        assert(__tests_run >= 0);                                              \
        __CHECK_NOT_IN_TEST_SUITE;                                             \
        if (__assertions_attempted == 0)                                       \
        {                                                                      \
            printf("%sNothing To Do (%d tests, %d assertions).%s Duration: "   \
                   "%f seconds\n",                                             \
                   __COLOR_BG_YELLOW, __tests_run, __assertions_attempted,     \
                   __COLOR_RESET, __runtime);                                  \
            puts("Did you include RUN_TEST(test_name) calls?");                \
            return EXIT_FAILURE;                                               \
        }                                                                      \
        if (__assertions_attempted == __assertions_succeeded)                  \
        {                                                                      \
            printf("%sOK (%d tests, %d assertions).%s Duration: %f seconds\n", \
                   __COLOR_BG_GREEN, __tests_run, __assertions_attempted,      \
                   __COLOR_RESET, __runtime);                                  \
            return EXIT_SUCCESS;                                               \
        }                                                                      \
        printf("%sErrors (%d out of %d assertions in %d tests).%s Duration: "  \
               "%f seconds\n",                                                 \
               __COLOR_BG_RED, __assertions_succeeded, __assertions_attempted, \
               __tests_run, __COLOR_RESET, __runtime);                         \
        return EXIT_FAILURE;                                                   \
    } while (0)

#endif /* PICOTEST_FRAMEWORK_H */
