CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: banhammer

banhammer: banhammer.o bf.o bv.o node.o ll.o speck.o ht.o parser.o
	$(CC) $(CFLAGS) -o banhammer banhammer.o bf.o bv.o node.o ll.o speck.o ht.o parser.o $(LFLAGS) #ht.o parser.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o banhammer

format:
	clang-format -i -style=file *.h *.c

scan-build: clean
	scan-build make
