#!/bin/sh
gcc -Wall -fsanitize=address test/tests.c -o testrunner
./testrunner
rm testrunner
