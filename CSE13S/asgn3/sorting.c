#include "bubble.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Argument options string
#define OPTIONS "bsqQan:r:p:"

// Eugene's and Sahiti's sections were very helful for
// teaching me how to use a set for parsing command line
// arguments. My implementation of an argument parser with
// a set is inspired from the material they covered in section
// and relied on the code for set.c and set.h provided on piazza.
typedef enum Sorts {
    BUBBLE, // 0
    SHELL, // 1
    SQUICK, // 2
    QQUICK, // 3
    ALL, // 4
    SIZE, // 5
    SEED, // 6
    ELEM // 7
} Sorts;

// Test harness for sorting algorithm implementations of asgn3.
// Given command line arguments from the options in "bsqQan:r:p:", the corresponding arguments
// of 'a' for all, 'b' for bubble sort, 's' for shell sort, 'q' for quick sort with a stack,
// 'Q' for quick sort with a queue, 'n' for random item array size, 'r' for random seed and 'p'
// for the number of sorted elements to print. If no or invalid arguments are entered in the command line,
// the correct usage of the sorting executable will be printed out onto the command line.

int main(int argc, char **argv) {
    int opt = 0;
    uint32_t size = 100; // Default as specified from asgn3 instructions
    uint32_t elem = 100; // Default as specified from asgn3 instructions
    uint32_t seed = 13371453; // Default as specified from asgn3 instructions

    Set sorts = set_empty(); // Use of set in CLI arguments

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b': sorts = set_insert(sorts, BUBBLE); break;
        case 's': sorts = set_insert(sorts, SHELL); break;
        case 'q': sorts = set_insert(sorts, SQUICK); break;
        case 'Q': sorts = set_insert(sorts, QQUICK); break;
        case 'n':
            sorts = set_insert(sorts, SIZE);
            size = atoi(optarg);
            break;
        case 'r':
            sorts = set_insert(sorts, SEED);
            seed = atoi(optarg);
            break;
        case 'a':
            for (Sorts i = BUBBLE; i <= QQUICK; i += 1) {
                sorts = set_insert(sorts, i);
            }
            break;
        case 'p':
            sorts = set_insert(sorts, ELEM);
            elem = atoi(optarg);
            break;
        default: break;
        }
    }

    // I adapted the synopsis, usage and option descriptions from the ones
    // produced by the sorting binary for asgn3. The binary was provided
    // by the cse13s-resources repo.
    bool emptyset = true;
    for (uint32_t c = 0; c < 5; c++) {
        if (set_member(sorts, c)) {
            emptyset = false;
        }
    }
    if (emptyset) {
        if (!(set_member(sorts, ELEM) || !set_member(sorts, SEED) || !set_member(sorts, SIZE))) {
            printf("Select at least one sort to perform.\n");
        }
        printf("SYNOPSIS\n   A collection of comparison-based sorting algorithms.\n\n");
        printf("USAGE\n   ./sorting [-absqQ] [-n length] [-p elements] [-r seed]\n\n");
        printf("OPTIONS\n");
        printf("   -a              Enable all sorts.\n   -b              Enable Bubble Sort.\n");
        printf("   -s              Enable Shell Sort.\n   -q              Enable Quick Sort "
               "(Stack).\n");
        printf("   -Q              Enable Quick Sort (Queue).\n   -n length       Specify number "
               "of array elements.\n");
        printf("   -p elements     Specify number of elements to print.\n   -r seed         "
               "Specify random seed.\n");
        return 0;
    }

    // Checks if valid array length was entered
    if (size <= 0) {
        printf("Invalid array length.\n");
        return 0;
    }

    // If size of array is less than desired items to print, just print
    // available items
    if (elem > size) {
        elem = size;
    }

    // Generate random item array
    srandom(seed);
    uint32_t arra[size];
    for (uint32_t c = 0; c < size; c++) {
        arra[c] = random();
    }

    // Bubble sort
    if (set_member(sorts, BUBBLE)) {
        bubble_sort(arra, size);
        printf("Bubble Sort\n");
        printf("%d elements, %d moves, %d compares", size, bmoves, bcomps);
        for (uint32_t c = 0; c < elem; c++) {
            if (((c) % 5) == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, arra[c]);
        }
        bmoves = 0;
        bcomps = 0;
        srandom(seed);
        for (uint32_t c = 0; c < size; c++) {
            arra[c] = random();
        }
        printf("\n");
    }

    // Shell sort
    if (set_member(sorts, SHELL)) {
        printf("Shell Sort\n");
        shell_sort(arra, size);
        printf("%d elements, %d moves, %d compares", size, bmoves, bcomps);
        for (uint32_t c = 0; c < elem; c++) {
            if (((c) % 5) == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, arra[c]);
        }
        bmoves = 0;
        bcomps = 0;
        srandom(seed);
        for (uint32_t c = 0; c < size; c++) {
            arra[c] = random();
        }
        printf("\n");
    }

    // Quicksort with stack
    if (set_member(sorts, SQUICK)) {
        printf("Quick Sort (Stack)\n");
        quick_sort_stack(arra, size);
        printf("%d elements, %d moves, %d compares\n", size, bmoves, bcomps);
        printf("Max stack size: %d", max_stack_size);
        for (uint32_t c = 0; c < elem; c++) {
            if (((c) % 5) == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, arra[c]);
        }
        bmoves = 0;
        bcomps = 0;
        srandom(seed);
        for (uint32_t c = 0; c < size; c++) {
            arra[c] = random();
        }
        printf("\n");
    }

    // Quicksort with queue
    if (set_member(sorts, QQUICK)) {
        printf("Quick Sort (Queue)\n");
        quick_sort_queue(arra, size);
        printf("%d elements, %d moves, %d compares\n", size, bmoves, bcomps);
        printf("Max queue size: %d", max_queue_size);
        for (uint32_t c = 0; c < elem; c++) {
            if (((c) % 5) == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, arra[c]);
        }
        bmoves = 0;
        bcomps = 0;
        srandom(seed);
        for (uint32_t c = 0; c < size; c++) {
            arra[c] = random();
        }
        printf("\n");
    }

    return 0;
}