# ancarda/picotest

[![License](https://img.shields.io/github/license/ancarda/picotest.svg)](https://choosealicense.com/licenses/agpl-3.0/)

PicoTest was written as a learning exercise and is not meant to be a serious
testing framework.

## Example Usage

```c
#include "picotest/lib/framework.h"

IT_SHOULD(do_nothing, {
    // A test that does nothing will show up as a warning
})

IT_SHOULD(pass, {
    char* a;
    char* b;

    a = "foobar";
    b = strdup(a);

    ASSERT_STR_EQ(a, b);
})

IT_SHOULD(fail, {
    ASSERT_INT_EQ(1, 2);
})

int main()
{
    BEGIN_TESTING;

    RUN_TEST(do_nothing);
    RUN_TEST(pass);
    RUN_TEST(fail);

    CONCLUDE_TESTING;
}
```

## Writing Tests

A test is named by what kind of checks it will perform. For instance, "it
should calculate employee salary" would setup the application to do just that.
Then, it'll do some assertions. A test should have 1 or more assertions. A
test with zero assertions causes a warning to display on the screen, but will
not make the test runner exit with 0.

### Assertions

Failure messages are printed with `printf`. Using the wrong assertion can lead
to a segmentation fault. Do not pass in pointers unless instructed.

 * `ASSERT_STR_EQ(*a, *b)` -- uses `strcmp`, prints with `%s`.
 * `ASSERT_INT_EQ(a, b)`   -- uses `==`, prints with `%d`.
 * `ASSERT_ULONG_EQ(a, b)` -- uses `==`, prints with `%lu`.
 * `ASSERT_NOT_NULL(*a)`   -- uses `==`, does not print anything.
 * `ASSERT_NULL(*a)`       -- uses `==`, does not print anything.

### Test Suites

You may want to break up your tests into logical chunks. You can do this with
the test suite macros:

```c
int main()
{
    BEGIN_TESTING;

    BEGIN_TEST_SUITE(Unit Testing Basics);
        RUN_TEST(do_nothing);
        RUN_TEST(pass);
        RUN_TEST(fail);
    END_TEST_SUITE;

    BEGIN_TEST_SUITE(Authentication Component);
        RUN_TEST(check_some_stuff);
        RUN_TEST(do_another_test);
    END_TEST_SUITE;

    CONCLUDE_TESTING;
}
```

You can, of course, put the test suite in another function, so between BEGIN
and CONCLUDE TESTING blocks, you only have function calls for logical groups
of tests.

## Running The Tests

Simply compile with `gcc` or your favorite C compiler. You can then run the
resulting binary. Assuming your tests were in `test/tests.c`:

    gcc -Wall -fsanitize=address test/tests.c -o testrunner
    ./testrunner

Note, if you omit `CONCLUDE_TESTING`, you will not get a summary or a return
code; the latter being important if you want to run your tests in a CI system.
