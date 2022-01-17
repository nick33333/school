#include "graph.h"

#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Vertices.h

struct Graph { // Abstraction of a graph
    uint32_t vertices; // Number of Vertices that we got
    bool undirected; // Is this an undirected graph?
    bool visited[VERTICES]; // Where have we gone?
    uint32_t matrix[VERTICES][VERTICES]; // Adjacency matrix that holds weights
};

// visited and matrix have fixed lengths given from the VERTICES macro
// In asgn3 we allocated memory because our arrays were dynamic
// In asgn4 our graph has a max of 26 vertices
// edge with a 0 is invalid, but we come back to overwrite some of them

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *g = (Graph *) malloc(sizeof(
        Graph)); // When we called malloc, we implicitly (not rlly) allocated mem for our arrays
    g->vertices = vertices;
    g->undirected = undirected;
    for (int i = 0; i < VERTICES; i++) {
        g->visited[i] = false; // visited starts out as false
        for (int j = 0; j < VERTICES; j++) {
            g->matrix[i][j] = 0;
        }
    }
    return g;
}

void graph_delete(Graph **g) {
    if (*g && (*g)->visited && (*g)->matrix) {
        free(*g);
        *g = NULL;
    }
    return;
}

uint32_t graph_vertices(Graph *g) { // Returns the number of vertices in a graph
    return g->vertices;
}

bool graph_add_edge(Graph *g, uint32_t i, uint32_t j, uint32_t k) {
    if ((i <= g->vertices) && (j <= g->vertices)) { // I think this is right
        g->matrix[i][j] = k;
        if (g->undirected) {
            g->matrix[j][i] = k;
        }
        return true;
    } else {
        return false;
    }
}

// Edge exists if there is a positive non-zero weight at i,j
bool graph_has_edge(Graph *g, uint32_t i, uint32_t j) {
    if ((i <= g->vertices) && (j <= g->vertices) && (g->matrix[i][j] > 0)) {
        return true;
    } else {
        return false;
    }
}

uint32_t graph_edge_weight(Graph *g, uint32_t i, uint32_t j) {
    if ((i <= g->vertices) && (j <= g->vertices) && (g->matrix[i][j] > 0)) {
        return g->matrix[i][j];
    } else {
        return 0;
    }
}

bool graph_visited(Graph *g, uint32_t v) {
    return g->visited[v];
}

bool graph_mark_visited(Graph *g, uint32_t v) { // Not too sure about this one
    if (v <= g->vertices) {
        g->visited[v] = true;
        return true;
    } else {
        return false;
    }
}

bool graph_mark_unvisited(Graph *g, uint32_t v) { // Not too sure about this one
    if (v <= g->vertices) {
        g->visited[v] = false;
        return true;
    } else {
        return false;
    }
}

void graph_print(Graph *g) {
    printf("Number of graph vertices: %d\n", graph_vertices(g));
    printf("Is graph undirected? ");
    if (g->undirected) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    printf("Graph visited vertices: \n");
    for (uint32_t c = 0; c < g->vertices; c++) {
        if (graph_visited(g, c)) {
            printf(" YES ");
        } else {
            printf(" NO ");
        }
    }
    printf("\n");
    printf("Graph matrix: \n");
    for (uint32_t c = 0; c < g->vertices; c++) {
        for (uint32_t k = 0; k < g->vertices; k++) {
            printf(" %d ", g->matrix[c][k]);
        }
        printf("\n");
    }
}
