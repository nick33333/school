#include "hamming.h"

#include <stdio.h>

// The hamming module contains the lookup table, ham_encode function and
// ham_decode funtion. The hamming module is used in encode.c and decode.c to
// help facilitate the conversion of 8-bit characters into 2 8-bit hamming codes
// which can then be corrected (if an erroneous bit flip occured) and packed
// back into a decoded message. Each hammign code carryies a nibble from the
// original 8-bit character along with 4 parity bits.

// Make G in encode.c
// Make Ht in decode.c
// Make lookup table here

static HAM_STATUS lookup[16] = { HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR,
    2, HAM_ERR, 1, 0, HAM_ERR };

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *m = bm_from_data(msg, 4);
    BitMatrix *coded = bm_multiply(m, G);
    uint8_t code = bm_to_data(coded);
    bm_delete(&m);
    bm_delete(&coded);
    return code;
}

// Takes in 8-bit hamming codes
HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    BitMatrix *c = bm_from_data(code, 8); // bm of code
    BitMatrix *err = bm_multiply(c, Ht); // bm of error syndrome
    uint8_t e = bm_to_data(err); // uint8 of error syndrome
    bm_delete(&err);
    bm_delete(&c);
    // printf("Ham status = %d\n",lookup[e]);
    if (e == 0) {
        *msg = code;
        // printf("HAM ok\n");
        return HAM_OK;
    } else if (lookup[e] != HAM_ERR) {
        code ^= 1 << lookup[e];
        *msg = code;
        // printf("HAM correct\n");
        return HAM_CORRECT;
    } else {
        *msg = code;
        // printf("HAM error\n");
        return HAM_ERR;
    }
}
