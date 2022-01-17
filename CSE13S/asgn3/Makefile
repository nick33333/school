C = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: sorting

sorting: sorting.o bubble.o shell.o stack.o queue.o quick.o set.o stats.o
	$(CC) $(CFLAGS) -o sorting sorting.o bubble.o shell.o stack.o queue.o quick.o  set.o stats.o $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o sorting

format:
	clang-format -i -style=file *.h *.c

scan-build: clean
	scan-build make
