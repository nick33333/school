#include "bm.h"

#include "bv.h"

#include <stdio.h>
#include <stdlib.h>

// bm.c contains my implementation of the bit matrix ADT. Eugene's and Sahiti's
// sections along with Eric's tutoring session helped me a lot with putting
// everything together. The bm =ADT relies on many of the bitwise operations
// created in bv. Bit Matrices will be the ADT most worked with in this
// assignment.

struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

// Creates a pointer to a BitMatrix
BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    if (m) {
        m->rows = rows;
        m->cols = cols;
        m->vector = bv_create(rows * cols);
    }
    if (!m) {
        free(m);
        m = NULL;
    }
    return m;
}

// Deletes BitMatrix
void bm_delete(BitMatrix **m) {
    if (*m) {
        bv_delete(&(*m)->vector);
        free(*m);
        *m = NULL;
    }
    return;
}

// Returns rows of BitMatrix
uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

// Returns cols of BitMatrix
uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

// r and c are matrix indices
void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, r * bm_cols(m) + c);
    return;
}

// Clears bm bit
void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * bm_cols(m) + c);
    return;
}

// Gets bit of bm through bv function
uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, r * bm_cols(m) + c);
}

// Converts data to a matrix
// Convert length number of bits into a bm
BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *m = bm_create(1, length);
    // every cth bit must be set
    for (uint32_t c = 0; c < length; c++) {
        // check bit value
        if (byte & (1 << c)) {
            bm_set_bit(m, 0, c);
        } else {
            bm_clr_bit(m, 0, c);
        }
    }
    return m;
}

// Converts matrix to data
uint8_t bm_to_data(BitMatrix *m) {
    uint8_t val = 0;
    for (uint32_t c = 0; c < m->cols; c++) {
        if (bm_get_bit(m, 0, c)) {
            val |= 1 << c;
        } else {
            val &= ~(1 << c);
        }
    }
    return val;
}

// If you multiply m with G, m=A and G=B
// Can initialize G and H in encode.c and decode.c respectively
// in their main functions
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    BitMatrix *z = bm_create(bm_rows(A), bm_cols(B));
    if (z == NULL) {
        return NULL;
    }

    for (uint32_t i = 0; i < bm_rows(z); i++) {
        for (uint32_t j = 0; j < bm_cols(z); j++) {
            for (uint32_t k = 0; k < bm_rows(B); k++) {
                // printf("A has : %d ",bm_get_bit(A,i,k));
                // printf("B has : %d",bm_get_bit(B,k,j));
                uint8_t prod = bm_get_bit(A, i, k) & bm_get_bit(B, k, j);
                // printf("prod is : %d \n\n",prod);
                bv_xor_bit(z->vector, i * bm_cols(z) + j, prod);
            }
        }
    }
    return z;
}

void bm_print(BitMatrix *m) {
    for (uint32_t i = 0; i < bm_rows(m); i++) {
        for (uint32_t j = 0; j < bm_cols(m); j++) {
            if (bm_get_bit(m, i, j)) {
                printf(" 1 ");
            } else {
                printf(" 0 ");
            }
        }
        printf("\n");
    }
}
