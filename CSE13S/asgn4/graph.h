#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdbool.h>
#include <stdint.h>

typedef struct Graph Graph;

Graph *graph_create(uint32_t vertices, bool undirected);

void graph_delete(Graph **g);

uint32_t graph_vertices(Graph *g);

bool graph_add_edge(Graph *g, uint32_t i, uint32_t j, uint32_t k);

bool graph_has_edge(Graph *g, uint32_t i, uint32_t j);

uint32_t graph_edge_weight(Graph *g, uint32_t i, uint32_t j);

bool graph_visited(Graph *g, uint32_t v);

bool graph_mark_visited(Graph *g, uint32_t v);

bool graph_mark_unvisited(Graph *g, uint32_t v);

void graph_print(Graph *g);

#endif
