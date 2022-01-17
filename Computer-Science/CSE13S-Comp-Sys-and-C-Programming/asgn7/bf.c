#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <stdio.h>
#include <stdlib.h>

// Bloom filter module for tracking oldspeak and badspeak word hashes.
// Input is passed through the Bloom filter to determine if seeking through
// the hash table is necessary.

struct BloomFilter {
    uint64_t primary[2]; // Primary hash function salt .
    uint64_t secondary[2]; // Secondary hash function salt .
    uint64_t tertiary[2]; // Tertiary hash function salt .
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        // Grimm 's Fairy Tales
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        // The Adventures of Sherlock Holmes
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        // The Strange Case of Dr. Jekyll and Mr. Hyde
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    if (*bf) {
        bv_delete(&(*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

// uint32_t hash(uint64_t *salt, char *key)
void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t p = hash(bf->primary, oldspeak) % bf_size(bf);
    uint32_t s = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint32_t t = hash(bf->tertiary, oldspeak) % bf_size(bf);
    //printf("p: %d --- s: %d --- t: %d\n",p,s,t);
    bv_set_bit(bf->filter, p);
    bv_set_bit(bf->filter, s);
    bv_set_bit(bf->filter, t);
}

// if probe is true, oldspeak is GOOD, o.w. it is either OLD  or BAD
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t p = hash(bf->primary, oldspeak) % bf_size(bf);
    uint32_t s = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint32_t t = hash(bf->tertiary, oldspeak) % bf_size(bf);
    //printf("p: %d --- s: %d --- t: %d\n",p,s,t);

    if (bv_get_bit(bf->filter, p) && bv_get_bit(bf->filter, s) && bv_get_bit(bf->filter, t)) {
        return true;
    } else {
        return false;
    }
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t c = 0; c < bv_length(bf->filter); c++) {
        if (bv_get_bit(bf->filter, c)) {
            //printf("bit is %d\n",bv_get_bit(bf->filter, c));
            count += 1;
        }
    }
    return count;
}

void bf_print(BloomFilter *bf) {
    printf("[Bloom filter bv]\n");
    bv_print(bf->filter);
}
