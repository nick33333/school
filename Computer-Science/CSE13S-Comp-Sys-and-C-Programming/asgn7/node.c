#include "node.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node module for creating a means to store oldspeak and badspeak words.
// Nodes with an oldspeak word with NULL for its newspeak word are considered
// to have badspeak words. Otherwise the node contains an oldpeak word with a newspeak
// translation. Nodes also contain pointers to the nodes before and after to provide
// functionality when incorporated in a linked list.

// This strdup function was provided by Professor Long
#define strdupp(s) strcpy(malloc(strlen(s) + 1), s)

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        if (oldspeak != NULL) {
            n->oldspeak = strdupp(oldspeak);
            //printf("[NODE CREATE] allocated old\n");
        } else {
            n->oldspeak = NULL;
            //printf("[NODE CREATE] NULLed old\n");
        }

        if (newspeak != NULL) {
            n->newspeak = strdupp(newspeak);
            //printf("[NODE CREATE] allocated new\n");
        } else {
            n->newspeak = NULL;
            //printf("[NODE CREATE] NULLed new\n");
        }
        n->next = NULL;
        n->prev = NULL;
        return n;
    }
    return 0;
}

void node_delete(Node **n) {
    if (*n) {
        // might have to free and NULL old and new speak
        free((*n)->newspeak);
        free((*n)->oldspeak);
        free(*n);
        *n = NULL;
    }
    return;
}

// Provided by asgn7 pdf
void node_print(Node *n) {
    // printf("Node print\n");
    if (n->oldspeak != NULL && n->newspeak != NULL) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    } else if (n->oldspeak != NULL) {
        printf("%s\n", n->oldspeak);
    }
    return;
}
