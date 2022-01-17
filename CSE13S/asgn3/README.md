# Assignment 3

This assignment is comprised of a collection of sorting algorithms and a test harness for it. bubble.h, shell.h and quick.h along with the source and header files that they are dependent on make up the collection of sorting algorithms. sorting.c corresponds with the testing harness for this collection. Users may enter the arguments -a, -b, -s, -q, -Q, -n, -r or -p in any order to specify desired arguments: all, bubble sort, shell sort, quicksort with a stack, quicksort with a queue, array size, random seed or number of sorted items to print out. Arguments are not mutually exclusive and will not repeat outputs. The files stats.c and stats.h are helper files that I added to help keep track of statistics and to provide a global swap function for all my program files.

## Build

Use make scan-build to run static analyzer. Will check code for errors. Compiles code.

	$ make scan-build

## Running

Valid arguments are -a, -b, -s, -q, -Q, -n, -r and -p. 
	
	$ ./sorting [-absqQ] [-n length] [-r  random seed] [-p elements to print]

## Cleaning

Removes binary and object files made after building program.

	$ make clean

## Formatting

Runs clang-format on all targeted .c and .h files.

	$ make format
