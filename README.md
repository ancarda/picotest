# ancarda/picotest

_A really tiny, mostly useless unit testing framework for C_

PicoTest was written as a learning exercise to support my other learning
exercise; [tiny-ircd](https://github.com/ancarda/tiny-ircd).

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

    ASSERT_STR_EQ(a, b)
})

IT_SHOULD(fail, {
    ASSERT_INT_EQ(1, 2)
})

int main()
{
    BEGIN_TESTING

    RUN_TEST(do_nothing)
    RUN_TEST(pass)
    RUN_TEST(fail)

    CONCLUDE_TESTING
}
```

## Writing Tests

A test is named by what kind of checks it will perform. For instance, "it
should calculate employee salary" would setup the application to do just that.
Then, it'll do some assertions. A test should have 1 or more assertions. A
test with zero assertions causes a warning to display on the screen, but will
not make the test runner exit with 0.

## Assertions

Failure messages are printed with `printf`. Using the wrong assertion can lead
to a segmentation fault. Do not pass in pointers unless instructed.

 * `ASSERT_STR_EQ(a, b)` -- uses `strcmp`, prints with `%s`.
 * `ASSERT_INT_EQ(a, b)` -- uses `==`, prints with `%d`.
 * `ASSERT_NOT_NULL(a)`  -- uses `==`, does not print anything.
 * `ASSERT_NULL(a)`      -- uses `==`, does not print anything.

## Running The Tests

Simply compile with `gcc` or your favorite C compiler. You can then run the
resulting binary. Assuming your tests were in `test/tests.c`:

    gcc -Wall -fsanitize=address test/tests.c -o testrunner
    ./testrunner

Note, if you omit `CONCLUDE_TESTING`, you will not get a summary or a return
code; the latter being important if you want to run your tests in a CI system.
