# Assignment 6

The primary components of this assignment were the Huffman coding module, an I/O module, a Huffman coding encoder and a Huffman coding decoder. ADTs that provided essential functionality to these modules were Nodes, Codes, Priority Queues and Stacks. An additional executable file in this assignment was entropy which measured the chaos observed in the data held in a file. For encode, users may enter the arguments -h, -v, -i, -o. For decode, users may enter the arguments -h, -v, -i, -o. For entropy, users may enter the argument -h. The arguments [-hiov] correspond to help, input, output, and verbose. The input for entropy is read from stdin.

## Build

Use make scan-build to run static analyzer. Will check code for errors. Compiles code.

	$ make scan-build

## Running

### Encode

Valid arguments are -h, -i, and -o
	
	$ ./encode [-h help] [-v verbose] [-i input file] [-o output file]

### Decode

Valid arguments are -h, -v, -i, and -o
	
	$ ./decode [-h help] [-v verbose] [-i input file] [-o output file]

### Entropy

Valid arguments are -h
	
	$ ./entropy [-h help] < [input (read from stdin)]

## Cleaning

Removes binary and object files made after building program.

	$ make clean

## Formatting

Runs clang-format on all targeted .c and .h files.

	$ make format