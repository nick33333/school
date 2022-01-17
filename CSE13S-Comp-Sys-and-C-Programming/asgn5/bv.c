#include "bv.h"

#include <stdio.h>
#include <stdlib.h>

// bv.c contains my implementation of the bit vector ADT. Eugene's and Sahiti's
// sections helped me a lot with putting everything together.

struct BitVector {
    uint32_t length; // Length in bits.
    uint8_t *vector; // Array of bytes.
};

BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) calloc(1, sizeof(BitVector));
    if (v) {
        v->length = length;
        uint32_t val = length % 8 == 0 ? length / 8 : (length / 8) + 1;
        if (val > 0) {
            v->vector = (uint8_t *) calloc(val, sizeof(uint8_t));
        }
    }
    if (!v) {
        free(v);
        v = NULL;
        return 0;
    }
    return v;
}

void bv_delete(BitVector **v) {
    if (*v && (*v)->vector) {
        free((*v)->vector);
        (*v)->vector = NULL;
        free(*v);
        *v = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *v) {
    return v->length;
}

// Use bitwise OR for this
// Sets a bit at a specified position
void bv_set_bit(BitVector *v, uint32_t i) {
    uint32_t byte = i / 8;
    uint32_t offset = i % 8;
    v->vector[byte] |= 1 << offset;
}

// Use bitwise AND for this
// Clears a bit at a position
void bv_clr_bit(BitVector *v, uint32_t i) {
    uint32_t byte = i / 8;
    uint32_t offset = i % 8;
    v->vector[byte] &= ~(1 << offset);
}

// Almost like what peek is to pop for stacks
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    uint32_t byte = i / 8;
    uint32_t offset = i % 8;
    if (v->vector[byte] & (1 << offset)) {
        return 1;
    } else {
        return 0;
    }
}

// Addition mod 2 is like performing XOR
void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    uint32_t byte = i / 8;
    uint32_t offset = i % 8;
    v->vector[byte] ^= (bit << offset);
}

void bv_print(BitVector *v) {
    for (uint32_t k = 0; k < (v->length * 8); k++) {
        if (k % 8 == 0) {
            printf("|");
        }
        // printf(" %d ",bv_get_bit(v,k));
        if (bv_get_bit(v, k)) {
            printf(" 1 ");
        } else {
            printf(" 0 ");
        }
    }
    printf("\n");
}
