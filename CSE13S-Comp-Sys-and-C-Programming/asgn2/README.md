# Assignment 2

This assignment is comprised of my implementation of a math library and a test harness for it. mathlib.h and mathlib.c correspond to the mathlibrary while mathlib-test.c corresponds with the testing harness for it. Users can either include the mathlib.h library into their own programs or run the test harness to compare its performance with the math.h library. When using mathlib-test, users may enter the arguments -a, -s, -c, -t or -l in any order to specify desired output corresponding to all, arcsin, arccos, arctan or log. Arguments are not mutually exclusive and will not repeat outputs. Note about arcsin and arccos implementations: The highest recorded difference in the test harness is 5e-11, but it gets rounded up to 1e-10.

## Build

Use make scan-build to run static analyzer. Will check code for errors. Compiles code.

	$ make scan-build

## Running

Valid arguments are -a, -s, -c, -t or -l. 
	
	$ ./mathlib-test -a

## Cleaning

Removes binary and object files made after building program.

	$ make clean
