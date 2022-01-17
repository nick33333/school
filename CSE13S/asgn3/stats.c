#include "stats.h"

// My source file corresponding to my additional header file.
// Holds my swap function and statistic counts

int bcomps;
int bmoves;
int qsmax;

// I made this swap function from what I learned about pointers.
void myswap(uint32_t *x, uint32_t *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}
