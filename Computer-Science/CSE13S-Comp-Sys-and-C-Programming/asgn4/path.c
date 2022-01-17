#include "path.h"

#include <stdio.h>
#include <stdlib.h>

struct Path {
    Stack *vertices; // The vertices comprising the path
    uint32_t length; // The total length of the path
};

Path *path_create(void) {
    Path *p = (Path *) (malloc(sizeof(Path)));
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    return p;
}

void path_delete(Path **p) {
    if (*p && (*p)->length && (*p)->vertices) {
        // printf("%d",sizeof(&(*p)->vertices));
        stack_delete(&(*p)->vertices);
        (*p)->vertices = NULL;
        free(*p);
        *p = NULL;
    }
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *g) {
    //printf("path: Start Num of vertices  %d\n",stack_size(p->vertices));
    if (stack_size(p->vertices) >= 1) {
        uint32_t t;
        stack_peek(p->vertices, &t);
        //printf("path: Old length: %d\n",p->length);
        p->length += graph_edge_weight(g, t, v); // increase path length
        stack_push(p->vertices, v);
        //printf("path: New length: %d\n",p->length);

    } else {
        //printf("path: First push? %d\n",v);
        stack_push(p->vertices, v);
        //printf("path: New length: %d\n",p->length);
    }
    //printf("path: Num of vertices  %d\n",stack_size(p->vertices));
    if (v) {
        return true;
    } else {
        return false;
    }
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *g) {
    if (p && v && g) {
        uint32_t t;
        stack_pop(p->vertices, v);
        stack_peek(p->vertices, &t);
        //("pop: Old length: %d\n",p->length);
        //printf("pop: Peeked vertices item: [%d]\n",t);
        p->length -= graph_edge_weight(g, t, *v);
        //printf("New length: %d\n",p->length);
        // if (v == (p->vertices)->items[(p->vertices)->top]){
        return true;
    } else {
        return false;
    }
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    dst->length = src->length;
    stack_copy(dst->vertices, src->vertices);
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %d\n", p->length);
    fprintf(outfile, "Path: ");
    stack_print(p->vertices, outfile, cities);
}