#include "../lib/framework.h"

#include "replace.c"

int main()
{
    BEGIN_TESTING;

    test_str_replace_byte();

    CONCLUDE_TESTING;
}
