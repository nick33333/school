#include "bubble.h"

#include "stats.h"

// bubble.c is the source file associated with bubble.h
// and contains an implementation of bubble sort.
// The bubble_sort function drew a lot of inspiration
// from the pseudocode provided on the asgn3 istruction pdf.

extern int bcomps, bmoves;

void bubble_sort(uint32_t *arra, uint32_t n) {
    int arrlen = n;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int c = 1; c < arrlen; c++) { // "Occurence" of comparison
            bcomps += 1; // Increment comparison counter
            if (arra[c] < arra[c - 1]) {
                myswap(&arra[c], &arra[c - 1]);
                bmoves += 3; // Increment move counter (1 swap = 3 moves)
                swapped = true;
            }
        }
        arrlen -= 1;
    }
}
