//
// PicoTest Main File
//

#pragma once

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "private.h"
#include "assertions.h"

// This should be at the start of your main function.
// Right now it just prints the PicoTest header, but could in the future
// be used to do some setup.
#define BEGIN_TESTING do { \
    puts("PicoTest"); \
    puts("========"); \
    puts(""); \
    clock_gettime(CLOCK_MONOTONIC, &__tests_began); \
    } while (0)

// Begins a test suite; a collection of tests.
#define BEGIN_TEST_SUITE(suite_name) \
    do { \
        __CHECK_NOT_IN_TEST_SUITE; \
        __in_test_suite = true; \
        printf("%s:\n", __EXPAND(suite_name)); \
    } while (0)

// Defines a new test. Provide the test name, and a body (use curly braces).
// The body should contain one or more ASSERT_xxx calls.
#define IT_SHOULD(test_name, test_body) \
    int it_should_##test_name() { \
        char* __formatted_name = __str_replace_byte(__EXPAND(test_name), '_', ' '); \
        printf("  it should %s:", __formatted_name); \
        free(__formatted_name); \
        int __assertions_before_this_test = __assertions_attempted; \
        test_body \
        if (__assertions_before_this_test == __assertions_attempted) { \
            __TEST_EMPTY; \
        } \
        __TEST_PASSED; \
    }

// This should be used after BEGIN_TESTING in main().
// The name is the same as you provided to IT_SHOULD.
#define RUN_TEST(test_name) do { \
    it_should_##test_name(); \
    __tests_run++; \
    __tests_run_in_suite++; \
    } while (0)

// Ends a test suite.
#define END_TEST_SUITE \
    do { \
        __in_test_suite = false; \
        if (__tests_run_in_suite == 0) { \
            __SUITE_EMPTY; \
        } \
        puts(""); \
        __tests_run_in_suite = 0; \
    } while (0)

// This should be used after all RUN_TEST calls in main().
// It prints the overall score, and provides an exit value for CI systems.
#define CONCLUDE_TESTING do { \
    clock_gettime(CLOCK_MONOTONIC, &__tests_concluded); \
    float __runtime_s  = ((float) __tests_concluded.tv_sec  - __tests_began.tv_sec); \
    float __runtime_ns = (__tests_concluded.tv_nsec - __tests_began.tv_nsec); \
    float __runtime    = ((__runtime_s * 1000000000) + __runtime_ns) / 1000000000;  \
    puts(""); \
    assert(__assertions_attempted >= __assertions_succeeded); \
    assert(__assertions_attempted >= 0); \
    assert(__assertions_succeeded >= 0); \
    assert(__tests_run >= 0); \
    __CHECK_NOT_IN_TEST_SUITE; \
    if (__assertions_attempted == 0) { \
        printf("%sNothing To Do (%d tests, %d assertions).%s Duration: %f seconds\n", \
            __COLOR_BG_YELLOW, \
            __tests_run, \
            __assertions_attempted, \
            __COLOR_RESET, \
            __runtime \
        ); \
        puts("Did you include RUN_TEST(test_name) calls?"); \
        return EXIT_FAILURE; \
    } \
    if (__assertions_attempted == __assertions_succeeded) { \
        printf("%sOK (%d tests, %d assertions).%s Duration: %f seconds\n", \
            __COLOR_BG_GREEN, \
            __tests_run, \
            __assertions_attempted, \
            __COLOR_RESET, \
            __runtime \
        ); \
        return EXIT_SUCCESS; \
    } \
    printf( \
        "%sErrors (%d out of %d assertions in %d tests).%s Duration: %f seconds\n", \
        __COLOR_BG_RED, \
        __assertions_succeeded, \
        __assertions_attempted, \
        __tests_run, \
        __COLOR_RESET, \
        __runtime \
    ); \
    return EXIT_FAILURE; \
    } while (0)
