.POSIX:

CFLAGS?=-ansi -Werror -Wpedantic -fsanitize=address

all: check

check:
	$(CC) $(CFLAGS) test/tests.c -o testrunner
	./testrunner
	$(RM) testrunner

format:
	clang-format -i lib/*.h test/*.c
