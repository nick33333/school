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
struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) calloc(capacity, sizeof(Node *));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        (*s)->items = NULL;
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {
    return s->top == 0;
}

bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false;
    } else {
        s->items[s->top] = n;
        s->top += 1;
        return true;
    }
}

bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    } else {
        s->top -= 1;
        *n = s->items[s->top];
        return true;
    }
}

void stack_print(Stack *s) {
    printf("[BEGIN STACK PRINT]\n");
    // Tells if stack is full and if stack is empty
    if (stack_full(s)) {
        printf("Stack full\n");
    } else {
        printf("Stack not full\n");
    }
    if (stack_empty(s)) {
        printf("Stack empty\n");
    } else {
        printf("Stack not empty\n");
    }
    // Prints stack elements including items from stack items array
    if (s) {
        printf("Stack top points to index: %d\n", s->top);
        printf("Stack capacity is        : %d\n", s->capacity);
        printf("Size of stack is         : %d\n", stack_size(s));
        printf("Stack items are:\n");
        for (uint32_t c = 0; c < s->capacity; c++) {
            // printf("item[%d]: %ld\n", c, s->items[c]);
            node_print(s->items[c]);
        }
    }
    return;
}
