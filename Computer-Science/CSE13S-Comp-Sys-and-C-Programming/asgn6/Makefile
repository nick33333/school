CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: encode decode entropy

encode: encode.o code.o huffman.o node.o pq.o helper.o io.o stack.o
	$(CC) $(CFLAGS) -o encode encode.o code.o huffman.o node.o pq.o helper.o io.o stack.o $(LFLAGS)

decode: decode.o code.o huffman.o node.o pq.o helper.o io.o stack.o
	$(CC) $(CFLAGS) -o decode decode.o code.o huffman.o node.o pq.o helper.o io.o stack.o $(LFLAGS)

entropy: entropy.o
	$(CC) $(CFLAGS) -o entropy entropy.o $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o encode decode entropy

format:
	clang-format -i -style=file *.h *.c

scan-build: clean
	scan-build make
