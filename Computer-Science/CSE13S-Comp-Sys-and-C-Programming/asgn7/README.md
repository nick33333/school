# Assignment 7

The primary components of this assignment was the banhammer file wall contained in banhammer.c. ADTs that provided essential functionality to this module were Nodes, Linked Lists, Bit Vectors, Hash Tables, and Bloom Filters. A given hash function from speck.c was used to help populate the Bloom filter and Hash Table. For banhammer, users may enter the arguments -h, -m, -t, -f, -s. The arguments [-hmtfs] correspond to help, enable move to front, hash table size, Bloom filter size and print statistics. The input for banhammer is read from stdin.

## Build

Use make scan-build to run static analyzer. Will check code for errors. Compiles code.

	$ make scan-build

## Running

### Banhammer

Valid arguments are -h, -m, -t, -f, -s
	
	$ ./banhammer [-h help] [-m move to front] [-t hash table size] [-f Bloom filter size] [-s Print statistics]  < [input (read from stdin)]

## Cleaning

Removes binary and object files made after building program.

	$ make clean

## Formatting

Runs clang-format on all targeted .c and .h files.

	$ make format