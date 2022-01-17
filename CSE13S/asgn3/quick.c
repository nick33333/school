#include "quick.h"

#include "queue.h"
#include "stack.h"
#include "stats.h"

// quick.c is the source file associated with quick.h
// and contains 2 implementations of quicksort.
// The 1st implementation is a non-recursive quicksort
// using a stack and the 2nd is a a non-recursive quicksort
// using a queue. The quick_partition, quick_sort_stack
// and quick_sort_queue functions drew a lot of inspiration
// from the pseudocode provided on the asgn3 istruction pdf.

int bcomps = 0;
int bmoves = 0;
uint32_t max_stack_size = 0;
uint32_t max_queue_size = 0;

// This is the partition sub-routine used in the following quicksort functions.
// My implementation of this function drew a lot of inspiration
// from the pseudocode provided on the asgn3 istruction pdf and in Sahiti's and
// Eugene's sections.
int64_t quick_partition(uint32_t *arra, int64_t lo, int64_t hi) {
    uint32_t pivot = arra[lo + (hi - lo) / 2];
    int64_t i = lo - 1;
    int64_t j = hi + 1;
    do {
        i += 1;
        while (arra[i] < pivot) { // Comparison occurs here
            i += 1;
            bcomps += 1;
        }
        if (arra[i] >= pivot) { // Comparison occurs here
            bcomps += 1;
        }
        j -= 1;
        while (arra[j] > pivot) { // Comparison occurs here
            j -= 1;
            bcomps += 1;
        }
        if (arra[j] <= pivot) { // Comparison occurs here
            bcomps += 1;
        }
        if (i < j) {
            myswap(&arra[i], &arra[j]); // Swaps (movements) of array items occur here
            bmoves += 3;
        }
    } while (i < j);
    return j;
}

// This is the quicksort function using a stack.
// My implementation of this function drew a lot of inspiration
// from the pseudocode provided on the asgn3 istruction pdf and in Sahiti's and
// Eugene's sections.
void quick_sort_stack(uint32_t *arra, uint32_t n) {
    int64_t lo = 0;
    int64_t hi = n - 1;
    Stack *s;
    s = stack_create(n);
    stack_push(s, lo);
    stack_push(s, hi);
    if (stack_size(s) > max_stack_size && (lo == hi)) { // max counter
        max_stack_size = 1;
    }
    while (stack_size(s) != 0) {
        stack_pop(s, &hi);
        stack_pop(s, &lo);
        int64_t p = quick_partition(arra, lo, hi); // Partition sub-routine call
        if (lo < p) {
            stack_push(s, lo);
            stack_push(s, p);
        }
        if (hi > (p + 1)) {
            stack_push(s, (p + 1));
            stack_push(s, hi);
        }
        if (stack_size(s) > max_stack_size) { // max counter
            max_stack_size = stack_size(s);
        }
    }
    stack_delete(&s); // delete stack when done, stats remain
}

// This is the quicksort function using a queue.
// My implementation of this function drew a lot of inspiration
// from the pseudocode provided on the asgn3 istruction pdf and in Sahiti's and
// Eugene's sections.
void quick_sort_queue(uint32_t *arra, uint32_t n) {
    int64_t lo = 0;
    int64_t hi = n - 1;
    Queue *q;
    q = queue_create(n);
    enqueue(q, lo);
    enqueue(q, hi);
    if (queue_size(q) > max_queue_size && (lo == hi)) { // max counter
        max_queue_size = 1;
    }
    while (queue_size(q) != 0) {
        dequeue(q, &lo);
        dequeue(q, &hi);
        int64_t p = quick_partition(arra, lo, hi); // Partition sub-routine call
        if (lo < p) {
            enqueue(q, lo);
            enqueue(q, p);
        }
        if (hi > (p + 1)) {
            enqueue(q, (p + 1));
            enqueue(q, hi);
        }
        if (queue_size(q) > max_queue_size) { // max counter
            max_queue_size = queue_size(q);
        }
    }
    queue_delete(&q); // delete queue when done, stats remain
}
