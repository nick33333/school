# Assignment 5

This assignment is comprised of a Hamming code module, a Hamming code encoder in the Hamming (8,4) scheme, a Hamming code decoder, an ADT for a BitVector and and an ADT for a BitMatrix. Additional executables are error and entropy which, respectively, inject noise into data and measure the chaos observed in the data held in a file. For encode, users may enter the arguments -h, -i, -o. For decode, users may enter the arguments -h, -i, -o, -v. For error, users may enter the arguments -h, -s, -e. For entropy, users may enter the argument -h. The arguments [-hiovse] correspond to help, input, output, verbose, random seed and error rate. The input for entropy is read from stdin.

## Build

Use make scan-build to run static analyzer. Will check code for errors. Compiles code.

	$ make scan-build

## Running

### Encode

Valid arguments are -h, -i, and -o
	
	$ ./encode [-h help] [-i input file] [-o output file]

### Decode

Valid arguments are -h, -v, -i, and -o
	
	$ ./decode [-h help] [-v verbose] [-i input file] [-o output file]

### Error

Valid arguments are -h, -s, -e
	
	$ ./error [-h help] [-s seed [-e error_rate]

### Entropy

Valid arguments are -h
	
	$ ./entropy [-h help] < [input (read from stdin)]

## Cleaning

Removes binary and object files made after building program.

	$ make clean

## Formatting

Runs clang-format on all targeted .c and .h files.

	$ make format
