#ifndef __PATH_H__
#define __PATH_H__

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct Path Path;

Path *path_create(void);

void path_delete(Path **p);

bool path_push_vertex(Path *p, uint32_t v, Graph *g);

bool path_pop_vertex(Path *p, uint32_t *v, Graph *g);

uint32_t path_vertices(Path *p);

uint32_t path_length(Path *p);

void path_copy(Path *dst, Path *src);

void path_print(Path *p, FILE *outfile, char *cities[]);

#endif
