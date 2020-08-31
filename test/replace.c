/* SPDX-License-Identifier: AGPL-3.0-or-later */

#include "../lib/framework.h"

IT_SHOULD(do_nothing_when_replacing_bytes_in_an_empty_string, {
    char* new;

    new = __str_replace_byte("", 1, 2);
    ASSERT_STR_EQ("", new);
    free(new);
});

IT_SHOULD(echo_the_given_string_when_replacing_a_non_present_byte, {
    char* new;

    new = __str_replace_byte("abcdef", 'g', 'h');
    ASSERT_STR_EQ("abcdef", new);
    free(new);
});

IT_SHOULD(replace_a_single_occurance, {
    char* new;

    new = __str_replace_byte("120456", '0', '3');
    ASSERT_STR_EQ("123456", new);
    free(new);
});

IT_SHOULD(replace_multiple_occurances, {
    char* new;

    new = __str_replace_byte("111333666", '1', '2');
    ASSERT_STR_EQ("222333666", new);
    free(new);
});

void test_str_replace_byte()
{
    BEGIN_TEST_SUITE(str_replace_byte);

    RUN_TEST(do_nothing_when_replacing_bytes_in_an_empty_string);
    RUN_TEST(echo_the_given_string_when_replacing_a_non_present_byte);
    RUN_TEST(replace_a_single_occurance);
    RUN_TEST(replace_multiple_occurances);

    END_TEST_SUITE;
}
