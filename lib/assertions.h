/**
 * PicoTest Default Assertions.
 *
 * You don't need to include this directly as it's already included by
 * framework.h
 */

#ifndef PICOTEST_ASSERTIONS_H
#define PICOTEST_ASSERTIONS_H

#include "private.h"
#include <string.h>

/**
 * Checks that x == y. Prints with %d.
 * Suitable for integers (int).
 */
#define ASSERT_INT_EQ(x, y)                                                    \
    do                                                                         \
    {                                                                          \
        __TRY_ASSERT({                                                         \
            if (x != y)                                                        \
            {                                                                  \
                printf("%sLine %d: ASSERT_INT_EQ: %d != %d", __ERR_MARKER,     \
                       __LINE__, x, y);                                        \
                __ASSERTION_FAILED;                                            \
            }                                                                  \
        });                                                                    \
    } while (0)

/**
 * Checks that x == y. Prints with %lu.
 * Suitable for unsigned longs (size_t, unsigned long).
 */
#define ASSERT_ULONG_EQ(x, y)                                                  \
    do                                                                         \
    {                                                                          \
        __TRY_ASSERT({                                                         \
            if (x != y)                                                        \
            {                                                                  \
                printf("%sLine %d: ASSERT_ULONG_EQ: %lu != %lu", __ERR_MARKER, \
                       __LINE__, x, y);                                        \
                __ASSERTION_FAILED;                                            \
            }                                                                  \
        });                                                                    \
    } while (0)

/**
 * Checks that x == y. Prints with %s.
 * Suitable for strings (char*).
 */
#define ASSERT_STR_EQ(x, y)                                                    \
    do                                                                         \
    {                                                                          \
        __TRY_ASSERT({                                                         \
            if (strcmp(x, y) != 0)                                             \
            {                                                                  \
                printf("%sLine %d: ASSERT_STR_EQ: {%s} != {%s}", __ERR_MARKER, \
                       __LINE__, x, y);                                        \
                __ASSERTION_FAILED;                                            \
            }                                                                  \
        });                                                                    \
    } while (0)

/**
 * Checks that x is not NULL. Prints generic message on failure.
 * Suitable for anything.
 */
#define ASSERT_NOT_NULL(x)                                                     \
    do                                                                         \
    {                                                                          \
        __TRY_ASSERT({                                                         \
            if (x == NULL)                                                     \
            {                                                                  \
                printf("%sLine %d: ASSERT_NOT_NULL: x == NULL", __ERR_MARKER,  \
                       __LINE__);                                              \
                __ASSERTION_FAILED;                                            \
            }                                                                  \
        });                                                                    \
    } while (0)

/**
 * Checks that x is NULL. Prints generic message on failure.
 * Suitable for anything.
 */
#define ASSERT_NULL(x)                                                         \
    do                                                                         \
    {                                                                          \
        __TRY_ASSERT({                                                         \
            if (x != NULL)                                                     \
            {                                                                  \
                printf("%sLine %d: ASSERT_NULL: x != NULL", __ERR_MARKER,      \
                       __LINE__);                                              \
                __ASSERTION_FAILED;                                            \
            }                                                                  \
        });                                                                    \
    } while (0)

#endif /* PICOTEST_ASSERTIONS_H */
