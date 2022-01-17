#include "ll.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked list module for a doubly linked list. Linked list items are nodes
// containing oldspeak and newspeak words as well as pointers to nodes before and
// after some current node.

uint64_t seeks = 0; // Number of seeks performed.
uint64_t links = 0; // Number of links traversed.

struct LinkedList {
    uint32_t length;
    Node *head; // Head Sentinel node
    Node *tail; // Tail Sentinel node
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    if (ll) {
        ll->length = 0;
        ll->mtf = mtf;

        ll->head = node_create(NULL, NULL);
        //printf("[LL CREATE] made head\n");
        ll->tail = node_create(NULL, NULL);
        //printf("[LL CREATE] made tail\n\n");
        ll->head->next = ll->tail;
        ll->tail->prev = ll->head;
    }
    return ll;
}

void ll_delete(LinkedList **ll) { // there may be a better way of deleting
    Node *tmp = (*ll)->head->next;
    Node *tmp2;
    node_delete(&(*ll)->head);
    while (tmp->next != NULL) {
        tmp2 = tmp->next;
        node_delete(&tmp);
        tmp = tmp2;
    }
    node_delete(&tmp);
    tmp = NULL;
    tmp2 = NULL;
    free(*ll);
    *ll = NULL;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    // start 1 node past head
    Node *tmp = ll->head->next;
    seeks += 1;
    while (tmp->next != NULL) {
        if (strcmp(tmp->oldspeak, oldspeak) == 0) { // may want to use strcmp
            //printf("strcmp passed\n");
            if (ll->mtf == true) {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                tmp->next = ll->head->next;
                tmp->prev = ll->head;
                ll->head->next = tmp;
                tmp->next->prev = tmp;
            }
            return tmp;
        } else {
            links += 1;
            tmp = tmp->next;
        }
    }
    return NULL;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (ll_lookup(ll, oldspeak)) {
        //printf("[ll.c] reject dat insert for [%s] bruh\n", oldspeak);
        return;
    } else {
        Node *n = node_create(oldspeak, newspeak);
        n->next = ll->head->next;
        n->prev = ll->head;
        ll->head->next = n;
        n->next->prev = n;
        ll->length += 1;
        return;
    }
}

void ll_print(LinkedList *ll) {
    //printf("[ll.c]<BEGINNING NODE PRINT>\n");
    Node *tmp = ll->head;
    while (tmp->next != NULL) {
        node_print(tmp);
        tmp = tmp->next;
    }
    //printf("\n");
}
