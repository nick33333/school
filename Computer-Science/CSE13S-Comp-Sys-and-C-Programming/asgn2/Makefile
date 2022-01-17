C = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: mathlib-test

mathlib-test: mathlib-test.o mathlib.o
	$(CC) $(CFLAGS) -o mathlib-test mathlib-test.o mathlib.o $(LFLAGS)

mathlib-test.o: mathlib-test.c
	$(CC) -c mathlib-test.c

mathlib.o: mathlib.c
	$(CC) -c mathlib.c 

clean:
	rm -f *.o mathlib-test

clang-format:
	clang-format -i -style=file *.h *.c

scan-build: clean
	scan-build make
