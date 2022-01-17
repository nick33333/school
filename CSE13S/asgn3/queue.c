#include "queue.h"

#include "stats.h"

// Sahiti's and Eugene's sections helped me a lot with figuring out
// the  functionality of the queue ADT. I also took a lot of
// inpiration from the code provided to us by the asgn3
// instruction pdf.

struct Queue { // change from typedef later
    uint32_t head;
    uint32_t tail;
    uint32_t queue_size;
    uint32_t capacity;
    int64_t *items;
};

Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) {
        q->head = 0; // Is 0 initially, gets shifted with dequeue (first in position)
        q->tail
            = 0; // Is 0 initially, gets shifted with enqueue (last in position), SOMETHING important about q->tail = q->tail%q->capacity
        q->queue_size = 0;
        q->capacity = capacity;
        q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

bool queue_empty(Queue *q) {
    return q->queue_size == 0;
}
bool queue_full(Queue *q) {
    return q->queue_size == q->capacity;
}
uint32_t queue_size(Queue *q) {
    return q->queue_size;
}

bool enqueue(Queue *q, int64_t i) { // Should fit in q->size+=1, adds item to tail position
    if (q->queue_size == q->capacity) {
        return false;
    }
    q->items[q->tail] = i;
    q->queue_size += 1;
    q->tail = (q->tail + 1) % (q->capacity);
    return true;
}
bool dequeue(Queue *q,
    int64_t *i) { // Should fit in q->size-=1, *i will store dequeued item (item in head position)
    if (queue_empty(q)) {
        return false;
    }
    q->queue_size -= 1;
    *i = q->items[q->head];
    q->head = (q->head + 1) % (q->capacity);
    return true;
}

void queue_delete(Queue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

void queue_print(Queue *q) {
    printf("[BEGIN QUEUE PRINT]\n");
    // Tells if queue is full and if queue is empty
    if (queue_full(q)) {
        printf("Queue full\n");
    } else {
        printf("Queue not full\n");
    }
    if (queue_empty(q)) {
        printf("Queue empty\n");
    } else {
        printf("Queue not empty\n");
    }
    // Prints queue elements including items from queue items array
    if (q) {
        printf("Queue tail points to index: %d\n", q->tail);
        printf("Queue head points to index: %d\n", q->head);
        printf("Queue capacity is        : %d\n", q->capacity);
        printf("Size of Queue is         : %d\n", queue_size(q));
        printf("Queue items are:\n");
        for (uint32_t c = 0; c < q->capacity; c++) {
            printf("item[%d]: %ld\n", c, q->items[c]);
        }
    }
    return;
}
