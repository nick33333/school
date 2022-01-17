#ifndef __STATS_H__
#define __STATS_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// My additional header file holding my swap function and statistic counts

extern int bcomps;
extern int bmoves;
extern int qsmax;

void myswap(uint32_t *x, uint32_t *y);

#endif