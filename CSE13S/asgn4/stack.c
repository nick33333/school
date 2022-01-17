#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Sahiti's and Eugene's sections helped me a lot with figuring out
// the  functionality of the stack ADT. I also took a lot of
// inpiration from the code provided to us by the asgn3
// instruction pdf.

// Stack structure which is 16 bytes in size
struct Stack { // Stack is an ADT // change from typedef later
    uint32_t top; // Index of the next empty slot.
    uint32_t capacity; // Number of items that can be pushed.
    uint32_t *items; // Pointer to an array of items , each with type int64_t.
};
// Stack constructor provided by asgn3 pdf
// Returns pointer to block of memory for stack to inhabit
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(
        Stack)); // creates stack container and gives a pointer to something the size of stack (16 bytes); allocated for stack structure
    if (s) { // if allocation succeeded, allocate things in stack ADT
        s->top = 0; // uint32_t integral value for top
        s->capacity = capacity; // uint32_t integral value for cap
        s->items = (uint32_t *) calloc(
            capacity, sizeof(uint32_t)); // uint64_t integral value for item pointer to block of mem
        if (!s->items) { // if allocation failed...
            free(s); // free stack
            s = NULL; // null the pointer
        }
    }
    return s;
}

// Stack is full when its top is equal to its cap
// Top always points to the next place we will put something
// If top points to 16 we are actually past the end of stack
// because numbers go from 0-15
bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

// Stack is empty when its top is equal to 0.
// If true this means that nothing is on the stack
// and s top points to slot 0
bool stack_empty(Stack *s) {
    return s->top == 0;
}

// item i is a value to set to your top pointer
bool stack_push(Stack *s,
    uint32_t
        i) { // if we want to push something onto the stack take the pointer of the stack and the item we want to push
    if (stack_full(s)) { // if stack is full
        s->capacity *= 2; // double capacity
        s->items = (uint32_t *) realloc(s->items,
            s->capacity
                * sizeof(
                    uint32_t)); // call realloc --> we extended memory region or found new larger space to copy stack
    }
    s->items[s->top] = i;
    s->top += 1; // After pushing item, move top up one
    return true;
}

bool stack_pop(Stack *s, uint32_t *i) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *i = s->items[s->top];
    return true;
}

bool stack_peek(Stack *s, uint32_t *i) {
    if (stack_empty(s)) {
        return false;
    }
    *i = s->items[(s->top) - 1];
    return true;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

void stack_copy(Stack *dst, Stack *src) {
    if (dst->capacity >= src->capacity) {
        dst->top = src->top;
        for (uint32_t c = 0; c < src->top; c++) {
            dst->items[c] = src->items[c];
        }
    }
    return;
}

void softstack_print(Stack *s, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        printf("%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}