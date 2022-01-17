#include "pq.h"

#include "node.h"

#include <stdio.h>
#include <stdlib.h>

// Sahiti's and Eugene's sections helped me a lot with figuring out
// the  functionality of the queue ADT. I also took a lot of
// inpiration from the code provided to us by the asgn3
// instruction pdf.

struct PriorityQueue { // change from typedef later
    uint32_t head;
    uint32_t tail;
    uint32_t queue_size;
    uint32_t capacity;
    Node **items;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (pq) {
        pq->head = 0; // Is 0 initially, gets shifted with dequeue (first in position)
        pq->tail = 0; // Is 0 initially, gets shifted with enqueue (last in position),
            // SOMETHING important about q->tail = q->tail%q->capacity
        pq->queue_size = 0;
        pq->capacity = capacity;
        pq->items = (Node **) calloc(capacity, sizeof(Node *));
        if (!pq->items) {
            free(pq);
            pq = NULL;
        }
    }
    return pq;
}

bool pq_empty(PriorityQueue *pq) {
    return pq->queue_size == 0;
}
bool pq_full(PriorityQueue *pq) {
    return pq->queue_size == pq->capacity;
}
uint32_t pq_size(PriorityQueue *pq) {
    return pq->queue_size;
}

bool enqueue(PriorityQueue *pq,
    Node *n) { // Should fit in q->size+=1, adds item to tail position
    if (pq->queue_size == pq->capacity) {
        return false;
    } else {
        uint32_t slot = pq->tail;
        uint32_t tmp = ((pq->capacity) + slot - 1)
                       % (pq->capacity); // formula for previous slot in circular queue
        pq->items[pq->tail] = n;
        while (slot != pq->head) {
            // printf("slot:%d ---- tmp:%d\n",slot,tmp);
            if ((pq->items[slot])->frequency < (pq->items[tmp])->frequency) {
                // printf("Change slot freq: %d with tmp freq:
                // %d???\n",(pq->items[slot])->frequency,(pq->items[tmp])->frequency);
                pq->items[slot] = pq->items[tmp];
                pq->items[tmp] = n;
            }
            slot = tmp;
            tmp = ((pq->capacity) + slot - 1) % (pq->capacity);
        }

        // printf("tail number = %d --- head number = %d --- slot number = %d ---
        // tmp number = %d \n",pq->tail,pq->head,slot,tmp);

        pq->queue_size += 1;
        pq->tail = (pq->tail + 1) % (pq->capacity);
        return true;
    }
}

bool dequeue(PriorityQueue *pq,
    Node **n) { // Should fit in q->size-=1, *i will store dequeued
    // item (item in head position)
    if (pq_empty(pq)) {
        return false;
    } else {
        pq->queue_size -= 1;
        *n = pq->items[pq->head];
        pq->head = (pq->head + 1) % (pq->capacity);
        // printf("Dequeued node symbol: %c, frequency: %d\n", (*n)->symbol,
        // (*n)->frequency);
        return true;
    }
}

void pq_delete(PriorityQueue **pq) {
    if (*pq && (*pq)->items) {
        // for (uint32_t c=0; c<(*pq)->capacity; c++) {
        //     node_delete(&(*pq)->items[c]);
        // }
        free((*pq)->items);
        (*pq)->items = NULL;
        free(*pq);
        *pq = NULL;
    }
    return;
}

void pq_print(PriorityQueue *pq) {
    printf("[BEGIN QUEUE PRINT]\n");
    // Tells if queue is full and if queue is empty
    if (pq_full(pq)) {
        printf("Queue full\n");
    } else {
        printf("Queue not full\n");
    }
    if (pq_empty(pq)) {
        printf("Queue empty\n");
    } else {
        printf("Queue not empty\n");
    }
    // Prints queue elements including items from queue items array
    if (pq) {
        printf("Queue tail points to index: %d\n", pq->tail);
        printf("Queue head points to index: %d\n", pq->head);
        printf("Queue capacity is        : %d\n", pq->capacity);
        printf("Size of Queue is         : %d\n", pq_size(pq));
        printf("Queue items are:\n");
        for (uint32_t c = 0; c < pq->capacity; c++) {
            printf("%d -- ", c);
            Node *nn = pq->items[c];
            node_print(nn);
        }
    }
    return;
}
