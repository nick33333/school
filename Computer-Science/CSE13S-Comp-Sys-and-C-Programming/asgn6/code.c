#include "code.h"

#include "defines.h"
#include "helper.h"

#include <stdbool.h>
#include <stdio.h>

// No dynamic allocation, this is a struct literal
// Since we don't pass a pointer (c is not a pointer) we can't use ->
// -> is used to dereference pointer
// Instead we access top and bits through .
Code code_init(void) {
    Code c;
    c.top = 0;
    return c;
}

// Since these functions take in a Code pointer we need to use ->
// Will have to pass params with & though
// eg: code_size(&c);
uint32_t code_size(Code *c) {
    return c->top;
}

// Returns true if code struct is empty, o.w. false
bool code_empty(Code *c) {
    return c->top == 0;
}

// Returns true if code struct is full, o.w. false
bool code_full(Code *c) {
    return c->top == MAX_CODE_SIZE;
}

// Returns true if bit is successfully pushed to code, o.w. false
bool code_push_bit(Code *c, uint8_t bit) {
    if (c && !code_full(c)) {
        uint32_t byte = (c->top) / 8;
        uint32_t offset = (c->top) % 8;
        c->bits[byte] &= ~(1 << offset); // clears bit at offset position
        c->bits[byte] |= bit << offset;
        c->top += 1;
        return true;
    } else {
        return false;
    }
}

// Returns true if bit is successfully popped from code, o.w. false
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (c && !code_empty(c)) {
        c->top -= 1;
        uint32_t byte = (c->top) / 8;
        uint32_t offset = (c->top) % 8;
        if ((c->bits[byte]) & (1 << offset)) {
            *bit = 1;
        } else {
            *bit = 0;
        }
        return true;
    } else {
        return false;
    }
}

// Prints code contents for debugging
void code_print(Code *c) {
    (code_empty(c)) ? printf("Code is EMPTY!\n") : printf("Code is NOT EMPTY!\n");
    (code_full(c)) ? printf("Code is FULL!\n") : printf("Code is NOT FULL!\n");
    printf("Code TOP/SIZE: %d\n", code_size(c));
    printf("Code BITS: \n");
    for (uint32_t k = 0; k < ((((c->top) - 1) / 8) + 1) * 8; k++) {
        if (k % 8 == 0) {
            printf("|");
        }
        if (code_get_bit(c, k)) {
            printf(" 1 ");
        } else {
            printf(" 0 ");
        }
    }
    printf("\n");
    for (uint32_t k = 0; k < MAX_CODE_SIZE; k++) {
    }
    printf("\n");
}
