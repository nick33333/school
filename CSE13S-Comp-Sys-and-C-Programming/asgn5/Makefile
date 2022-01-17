CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: encode decode error entropy

error: error.o
	$(CC) $(CFLAGS) -o error error.o $(LFLAGS)

entropy: entropy.o
	$(CC) $(CFLAGS) -o entropy entropy.o $(LFLAGS)

decode: decode.o bm.o bv.o hamming.o 
	$(CC) $(CFLAGS) -o decode decode.o bm.o bv.o hamming.o $(LFLAGS)

encode: encode.o bm.o bv.o hamming.o 
	$(CC) $(CFLAGS) -o encode encode.o bm.o bv.o hamming.o $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o decode encode error entropy

format:
	clang-format -i -style=file *.h *.c

scan-build: clean
	scan-build make
