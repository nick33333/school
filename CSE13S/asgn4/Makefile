C = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: tsp

tsp: tsp.o graph.o stack.o path.o set.o
	$(CC) $(CFLAGS) -o tsp tsp.o graph.o stack.o path.o set.o $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o tsp

format:
	clang-format -i -style=file *.h *.c

scan-build: clean
	scan-build make
