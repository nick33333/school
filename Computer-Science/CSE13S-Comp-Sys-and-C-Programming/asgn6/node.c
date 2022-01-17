#include "node.h"

#include <stdio.h>
#include <stdlib.h>

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->symbol = symbol;
        n->frequency = frequency;
        n->left = NULL;
        n->right = NULL;
        return n;
    }
    return 0;
}

void node_delete(Node **n) {
    if (*n) {
        free(*n);
        *n = NULL;
    }
    return;
}

Node *node_join(Node *left, Node *right) {
    if (left && right) {
        uint64_t sum = (left->frequency) + (right->frequency);
        Node *n = node_create('$', sum);
        n->left = left;
        n->right = right;
        return n;
    }
    return 0;
}

void node_print(Node *n) {
    printf("Node frequency: %lu --- ", n->frequency);
    printf("Node symbol: %c\n", n->symbol);

    if (n->left != NULL) {
        printf("Has LEFT: %c\n", (n->left)->symbol);
    }
    if (n->right != NULL) {
        printf("Has RIGHT: %c\n", (n->right)->symbol);
    }
    return;
}
