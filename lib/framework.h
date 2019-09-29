//
// PicoTest Main File
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "private.h"
#include "assertions.h"

// This should be at the start of your main function.
// Right now it just prints the PicoTest header, but could in the future
// be used to do some setup.
#define BEGIN_TESTING \
    puts("PicoTest"); \
    puts("========"); \
    puts("");

// Defines a new test. Provide the test name, and a body (use curly braces).
// The body should contain one or more ASSERT_xxx calls.
#define IT_SHOULD(test_name, test_body) \
    int it_should_##test_name() { \
        printf("it should %s:", __EXPAND(test_name)); \
        int __assertions_before_this_test = __assertions_attempted; \
        test_body \
        if (__assertions_before_this_test == __assertions_attempted) { \
            __TEST_EMPTY; \
        } \
        __TEST_PASSED; \
    }

// This should be used after BEGIN_TESTING in main().
// The name is the same as you provided to IT_SHOULD.
#define RUN_TEST(test_name) \
    it_should_##test_name(); \
    __tests_run++;

// This should be used after all RUN_TEST calls in main().
// It prints the overall score, and provides an exit value for CI systems.
#define CONCLUDE_TESTING \
    puts(""); \
    assert(__assertions_attempted >= __assertions_succeeded); \
    assert(__assertions_attempted >= 0); \
    assert(__assertions_succeeded >= 0); \
    assert(__tests_run >= 0); \
    if (__assertions_attempted == 0) { \
        printf("%sNothing To Do (%d tests, %d assertions).%s\n", \
            __COLOR_BG_YELLOW, \
            __tests_run, \
            __assertions_attempted, \
            __COLOR_RESET \
        ); \
        puts("Did you include RUN_TEST(test_name) calls?"); \
        return EXIT_FAILURE; \
    } \
    if (__assertions_attempted == __assertions_succeeded) { \
        printf("%sOK (%d tests, %d assertions).%s\n", \
            __COLOR_BG_GREEN, \
            __tests_run, \
            __assertions_attempted, \
            __COLOR_RESET \
        ); \
        return EXIT_SUCCESS; \
    } \
    printf( \
        "%sErrors (%d out of %d assertions in %d tests).%s\n", \
        __COLOR_BG_RED, \
        __assertions_succeeded, \
        __assertions_attempted, \
        __tests_run, \
        __COLOR_RESET \
    ); \
    return EXIT_FAILURE;
