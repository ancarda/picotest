/* SPDX-License-Identifier: AGPL-3.0-or-later */

#include "../lib/framework.h"

#include "replace.c"

int main()
{
    BEGIN_TESTING;

    test_str_replace_byte();

    CONCLUDE_TESTING;
}
