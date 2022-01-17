# Assignment 4

This assignment is comprised of a solution to the travelling sales person problem using a depth first search function with a test harness for it. stack.h, path.h, graph.h along with the source and header files that they are dependent on make up a collection of abstract data types that are used in tandem for the recursive depth first search function. Users may enter the arguments -h, -v, -u, -i, -o in any order to specify desired arguments: help, verbose, undirected, inputfile, and outputfile. The arguments [vuio] are not mutually exclusive, but will all be overwritten by the -h command which prints out tsp's usage.

## Build

Use make scan-build to run static analyzer. Will check code for errors. Compiles code.

	$ make scan-build

## Running

Valid arguments are -h, -v, -u, -i, and -o
	
	$ ./sorting [-h help] [-v verbose] [-u undirected] [-i input file] [-o output file]

## Cleaning

Removes binary and object files made after building program.

	$ make clean

## Formatting

Runs clang-format on all targeted .c and .h files.

	$ make format