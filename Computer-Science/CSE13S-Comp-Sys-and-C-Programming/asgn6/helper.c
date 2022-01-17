#include "helper.h"
// Used in:
// code.c
// io.c

// Contains functions helpful for working with ADTs

// Returns true if node is a leaf, false o.w.
bool leaf_checker(Node *n) {
    return (n->left == NULL) && (n->right == NULL);
}

// Calculates bytes + remainder from leftover bits
int byte_cal(uint32_t bits) {
    int byte_raw = bits / 8;
    int byte_rem = 0;
    if ((bits % 8) > 0) {
        byte_rem += 1;
    }
    int byte_tot = byte_raw + byte_rem;
    return byte_tot;
}

// Use bitwise OR for this
// Sets a bit at a specified position
void set_bit(uint8_t buffer[], uint32_t i) {
    uint32_t byte = i / 8;
    uint32_t offset = i % 8;
    buffer[byte] &= ~(1 << offset);
    buffer[byte] |= 1 << offset;
}

// Use bitwise AND for this
// Clears a bit at a position
void clr_bit(uint8_t buffer[], uint32_t i) {
    uint32_t byte = i / 8;
    uint32_t offset = i % 8;
    buffer[byte] &= ~(1 << offset);
}

uint8_t get_bit(uint8_t buffer[], uint32_t i) {
    uint32_t byte = i / 8;
    uint32_t offset = i % 8;
    if (buffer[byte] & (1 << offset)) {
        return 1;
    } else {
        return 0;
    }
}

// Use bitwise OR for this
// Sets a bit at a specified position
void code_set_bit(Code *c, uint32_t i) {
    uint32_t byte = i / 8;
    uint32_t offset = i % 8;
    c->bits[byte] &= ~(1 << offset);
    c->bits[byte] |= 1 << offset;
    if (c->top < i) {
        c->top = i + 1;
    }
}

// Use bitwise AND for this
// Clears a bit at a position
void code_clr_bit(Code *c, uint32_t i) {
    uint32_t byte = i / 8;
    uint32_t offset = i % 8;
    c->bits[byte] &= ~(1 << offset);
}

uint8_t code_get_bit(Code *c, uint32_t i) {
    uint32_t byte = i / 8;
    uint32_t offset = i % 8;
    if (c->bits[byte] & (1 << offset)) {
        return 1;
    } else {
        return 0;
    }
}
