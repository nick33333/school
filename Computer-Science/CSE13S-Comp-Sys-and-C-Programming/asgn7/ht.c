#include "ht.h"

#include "ll.h"
#include "speck.h"

#include <stdio.h>
#include <stdlib.h>

// Hash table module for storing oldspeak and badspeak word nodes.
// Hash collisions are resolved by means of linked lists stored at
// hash indices in the hash table.

static uint32_t count = 0;

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        // Leviathan
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    for (uint32_t c = 0; c < (*ht)->size; c++) {
        if ((*ht)->lists[c] != NULL) {
            //printf("[ht.c] deleting a linked list in ht\n");
            ll_delete(&(*ht)->lists[c]);
        }
    }
    free((*ht)->lists);
    (*ht)->lists = NULL;
    free(*ht);
    *ht = NULL;
    //printf("[ht.c] deleted a ht\n");
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

// uint32_t hash(uint64_t *salt, char *key);
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t h_ind = hash(ht->salt, oldspeak) % ht_size(ht);
    //printf("[ht.c] h_ind in ht_lookup is [%d] for [%s]\n",h_ind, oldspeak);
    if (ht->lists[h_ind]) {
        Node *ntmp = ll_lookup(ht->lists[h_ind], oldspeak);
        if (ntmp) {
            return ntmp;
        }
    }
    //printf("[ht.c] nothing here at [%d] for [%s]\n", h_ind, oldspeak);
    return NULL;
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t h_ind = hash(ht->salt, oldspeak) % ht_size(ht);
    if (!ht->lists[h_ind]) {
        //printf("[ht.c] making NEW ll at [%d] in ht for [%s]\n",h_ind, oldspeak);
        // add to count for ht_count here
        count += 1;
        ht->lists[h_ind] = ll_create(ht->mtf);
    }
    ll_insert(ht->lists[h_ind], oldspeak, newspeak);
}

uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t c = 0; c < ht_size(ht); c++) {
        if (ht->lists[c]) {
            count += 1;
        }
    }
    return count;
}

void ht_print(HashTable *ht) {
    printf("here's the count [%d] \n", ht_count(ht));
    for (uint32_t c = 0; c < ht_size(ht); c++) {
        if (ht->lists[c]) {
            printf("idx[%d] ", c);
            ll_print(ht->lists[c]);
        }
    }
}
