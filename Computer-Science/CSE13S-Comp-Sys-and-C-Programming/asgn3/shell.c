#include "gaps.h"
#include "stats.h"

// shell.c is the source file associated with shell.h
// and contains an implementation of shell sort.
// The shell_sort function drew a lot of inspiration
// from the pseudocode provided on the asgn3 istruction pdf.

// GAPS is the length of the pratt sequence array from gaps.h
// gaps is the pratt sequence from gaps.h

void shell_sort(uint32_t *arra, uint32_t n) {
    for (int c = 0; c < GAPS; c++) { // GAPS and gaps are defined in gaps.h
        uint32_t gap = gaps[c];
        for (uint32_t i = gap; i < n; i += 1) { // "Occurence" of comparison
            uint32_t j = i;
            uint32_t temp = arra[i];
            bmoves += 1;
            while ((j >= gap) && (temp < arra[j - gap])) { // "Occurence" of comparison
                myswap(&arra[j], &arra[j - gap]);
                bcomps += 1;
                bmoves += 1; // change this to one and its ok for some reason
                j -= gap;
            }
            if ((j >= gap) && (temp >= arra[j - gap])) { // "Occurence" of comparison
                bcomps += 1;
            }
            arra[j] = temp;
            bmoves += 1;
        }
    }
    return;
}
