//
// Assertions for PicoTest.
//

#pragma once

#include <string.h>
#include "private.h"

// Checks that x == y. Suitable for integers (int).
#define ASSERT_INT_EQ(x, y) do { __TRY_ASSERT({ \
    if (x != y) { \
        printf("%sLine %d: ASSERT_INT_EQ: %d != %d",__ERR_MARKER, __LINE__, x, y); \
        __ASSERTION_FAILED; \
    }}); } while (0)

// Checks that x == y. Suitable for strings (char*).
#define ASSERT_STR_EQ(x, y) do { __TRY_ASSERT({ \
    if (strcmp(x, y) != 0) { \
        printf("%sLine %d: ASSERT_STR_EQ: {%s} != {%s}", __ERR_MARKER, __LINE__, x, y); \
        __ASSERTION_FAILED; \
    }}); } while (0)

// Checks that x is not NULL. Suitable for anything.
#define ASSERT_NOT_NULL(x) do { __TRY_ASSERT({ \
    if (x == NULL) { \
        printf("%sLine %d: ASSERT_NOT_NULL: x == NULL", __ERR_MARKER, __LINE__); \
        __ASSERTION_FAILED; \
    }}); } while (0)

// Checks that x is NULL. Suitable for anything.
#define ASSERT_NULL(x) do { __TRY_ASSERT({ \
    if (x != NULL) { \
        printf("%sLine %d: ASSERT_NULL: x != NULL", __ERR_MARKER, __LINE__); \
        __ASSERTION_FAILED; \
    }}); } while (0)
