#include "mathlib.h"

#include <math.h>
#include <stdbool.h> // I found Eugene's use of bool in section very helpful
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "asctl"

// The print_header function will print formatted headers to the functions specified
// in the command line when mathlib-test is executed.
static void print_header(char *s) {
    printf("  %-12s %-16s %-14s %-16s\n", "x", s, "Library", "Difference");
    printf(" %2s %17s %17s %17s\n", "-", "------", "-------", "----------");
}

// Given command line arguments from the options in 'asctl', the corresponding arguments
// of '\a' for all, '\s' for arcsin, '\c' for arccos, '\t' for arctan or '\l' for log will
// have their associated bools in the main function of mathlib-test set to true. With bools
// for these functions set to true, a table running through each functions output will be
// printed out onto the command line. If no or invalid arguments are entered in the command
// line, the correct usage of mathlib-test will be printed out onto the command line.
int main(int argc, char **argv) {
    int opt = 0; // From Eugene's section, store next option from getopt()
    bool arc_Sin = false;
    bool arc_Cos = false;
    bool arc_Tan = false;
    bool my_Log = false;
    bool no_arg = true;
    // Switch statement for parsing commandline arguments into bools associated with
    // functions from mathlib.
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            arc_Sin = true;
            arc_Cos = true;
            arc_Tan = true;
            my_Log = true;
            no_arg = false;
            break;
        case 's':
            arc_Sin = true;
            no_arg = false;
            break;
        case 'c':
            arc_Cos = true;
            no_arg = false;
            break;
        case 't':
            arc_Tan = true;
            no_arg = false;
            break;
        case 'l':
            my_Log = true;
            no_arg = false;
            break;
        default:
            printf("Program usage: ./mathlib-test -[asctl]\n");
            printf("  -a   Runs all tests (arcsin, arccos, arctan, log)\n");
            printf("  -s   Runs arcsin tests\n");
            printf("  -c   Runs arccos tests\n");
            printf("  -t   Runs arctan tests\n");
            printf("  -l   Runs log tests\n");
            return EXIT_FAILURE;
        }
    }
    // If no_arg=true, print out mathlib-test usage.
    if (no_arg) {
        printf("Program usage: ./mathlib-test -[asctl]\n");
        printf("  -a   Runs all tests (arcsin, arccos, arctan, log)\n");
        printf("  -s   Runs arcsin tests\n");
        printf("  -c   Runs arccos tests\n");
        printf("  -t   Runs arctan tests\n");
        printf("  -l   Runs log tests\n");
    }
    // If arc_Sin=true, print out table composed of header and a series of arcSin function outputs
    // along with differences between my function output and math.h function output.
    if (arc_Sin) {
        print_header("arcSin");
        for (double c = -1; c < 1; c += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", c, arcSin(c), asin(c),
                arcSin(c) - asin(c));
        }
    }
    // If arc_Cos=true, print out table composed of header and a series of arcCos function outputs.
    // along with differences between my function output and math.h function output.
    if (arc_Cos) {
        print_header("arcCos");
        for (double c = -1; c < 1; c += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", c, arcCos(c), acos(c),
                arcCos(c) - acos(c));
        }
    }
    // If arc_Tan=true, print out table composed of header and a series of arcTan function outputs.
    // along with differences between my function output and math.h function output.
    if (arc_Tan) {
        print_header("arcTan");
        for (double c = 1; c < 10; c += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", c, arcTan(c), atan(c),
                arcTan(c) - atan(c));
        }
    }
    // If my_Log=true, print out table composed of header and a series of Log function outputs.
    // along with differences between my function output and math.h function output.
    if (my_Log) {
        print_header("Log");
        for (double c = 1; c < 10; c += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", c, Log(c), log(c), Log(c) - log(c));
        }
    }
    return EXIT_SUCCESS;
}
