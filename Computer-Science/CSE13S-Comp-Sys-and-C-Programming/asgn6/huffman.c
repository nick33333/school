#include "huffman.h"

#include "pq.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

// Postorder takes in some root node, a Code where tmp codes computed from
// travelling can be stored and a Code table where tmp codes are assigned for
// each non $ symbol
void postorder(Node *n, Code c, Code table[static ALPHABET]) {
    uint8_t tmp;
    if (n != NULL) {
        code_push_bit(&c, 0);
        postorder(n->left, c, table);
        code_pop_bit(&c, &tmp);

        code_push_bit(&c, 1);
        postorder(n->right, c, table);
        code_pop_bit(&c, &tmp);

        if ((n->left) == NULL && (n->right) == NULL) { // badddddd
            code_push_bit(&c, 0);
            code_pop_bit(&c, &tmp);
            table[n->symbol] = c;

            // printf("Symbol: %c\n",n->symbol);
            // code_print(&c);
        }
    }
    return;
}

// function takes in computed histogram and builds tree
Node *build_tree(uint64_t hist[static ALPHABET]) {
    uint32_t unicount = 0;
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) { // counts up unicount
            unicount += 1;
        }
    }
    PriorityQueue *pq = pq_create(unicount);
    for (int c = 0; c < ALPHABET; c++) {
        if (hist[c] > 0) {
            enqueue(pq, node_create(c, hist[c]));
        }
    }
    while (pq_size(pq) > 1) {
        Node *x;
        Node *y;
        dequeue(pq, &x);
        dequeue(pq, &y);
        Node *z = node_join(x, y);
        enqueue(pq, z);
    }
    Node *xyz;
    dequeue(pq, &xyz);
    pq_delete(&pq);
    return xyz;
}

// constructs code table with ALPHABET number of indices
void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    postorder(root, c, table);
    return;
}

void delete_tree(Node **root) {
    if (*root != NULL) {
        delete_tree(&((*root)->left));
        delete_tree(&((*root)->right));
        node_delete(&(*root));
        *root = NULL;
    }
    return;
}

// Reconstructs huffman tree from tree dump
Node *rebuild_tree(uint16_t nbytes, uint8_t treedump[static nbytes]) {
    Stack *s = stack_create(nbytes);
    for (uint16_t i = 0; i < nbytes; i++) {
        if (treedump[i] == 'L') {
            Node *n = node_create(treedump[i + 1], 0);
            stack_push(s, n);
            i += 1;
        } else {
            Node *right;
            Node *left;
            stack_pop(s, &right);
            stack_pop(s, &left);
            Node *j = node_join(left, right);
            stack_push(s, j);
        }
    }
    Node *n;
    stack_pop(s, &n);
    stack_delete(&s);
    return n;
}
