#include "graph.h"
#include "path.h"
#include "set.h"
#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOCK   4096
#define OPTIONS "hvui:o:"
static uint32_t count = 0;
static FILE *infile;
static FILE *outfile;
static char *input_file;
static char *output_file;
// Eugene's section was very helful for
// teaching me how to use a set for parsing command line
// arguments. My implementation of an argument parser with
// a set is inspired from the material they covered in section
// and relied on the code for set.c and set.h provided on piazza.

// This program serves as a test harness and source file for a solution to the
// travelling salesman problem using a depth first search function.
// Command line arguments from the options in "hvui:o:", correspond to the
// arguments 'h' for help, 'v' for verbose output, 'u' for undirected, 'i' for
// input file, and 'o' for outputfile. If no arguments or invalid arguments are
// entered in the command line, the correct usage of the tsp program will be
// printed out onto the command line.

typedef enum Args {
    HELP, // 0
    VERBOSE, // 1
    UNDIR, // 2
    INFILE, // 3
    OUTFILE // 4
} Args;

int main(int argc, char **argv) {

    // char *input_file;
    // char *output_file;
    int opt = 0;
    Set args = set_empty(); // Use of set in CLI arguments
    bool arg_error = true;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': args = set_insert(args, HELP); break;
        case 'v': args = set_insert(args, VERBOSE); break;
        case 'u': args = set_insert(args, UNDIR); break;
        case 'i':
            input_file = optarg;
            arg_error = false;
            args = set_insert(args, INFILE);
            break;
        case 'o':
            output_file = optarg;
            args = set_insert(args, OUTFILE);
            break;
        default: arg_error = true; break;
        }
    }

    if (arg_error || set_member(args, HELP)) {
        printf("SYNOPSIS\n");
        printf("  Traveling Salesman Problem using DFS.\n\n");
        printf("USAGE\n");
        printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
        printf("OPTIONS\n");
        printf("  -u             Use undirected graph.\n");
        printf("  -v             Enable verbose printing.\n");
        printf("  -h             Program usage and help.\n");
        printf("  -i infile      Input containing graph (default: stdin)\n");
        printf("  -o outfile     Output of computed path (default: stdout)\n");
        return 0;
    }

    void dfs(Graph * g, uint32_t v, Path * curr, Path * shortest, char *cities[], FILE *outfile,
        bool verbo);
    int q, c, i, j, k;
    char buffer[BLOCK];
    Graph *g;
    Path *curr = path_create();
    Path *shortest = path_create();
    // FILE *infile;
    // FILE *outfile;

    // Command Line Argument Parameters in Use Below

    // -h Help argument call

    // -i inputfile argument call
    if (set_member(args, INFILE)) {
        infile = fopen(input_file, "r"); // fopoen params: 1.) file to open 2.) mode
            // to open in // [argumen -i]
        if (infile == NULL) {
            fprintf(stderr, "Error: failed to open infile\n");
            return 1; // return 1 exits function, exit(1) would exit the program
        }
    } else {
        infile = stdin;
    }
    // -i inputfile argument call
    if (set_member(args, OUTFILE)) {
        outfile = fopen(output_file,
            "w"); // fopoen params: 1.) file to open 2.) mode to open in
        // // [argumen -i]
        if (outfile == NULL) {
            fprintf(stderr, "Error: failed to open outfile\n");
            return 1; // return 1 exits function, exit(1) would exit the program
        }
    } else {
        outfile = stdout;
    }

    // Parsing of infile
    // Vertices number will get taken first by q
    fscanf(infile, "%d\n", &q);
    if (q <= 0) {
        printf("Error: invalid number of vertices\n");
        return 0;
    }
    g = graph_create(q, set_member(args, UNDIR)); // [argument -u]
    char *cities[q];
    // Removes akward '\n' character left after fscanf
    fgets(buffer, sizeof(char), infile);
    // Fill cities array of size q with the loop below
    for (int c = 0; c < q; c++) {
        fgets(buffer, BLOCK, infile);
        buffer[strlen(buffer) - 2] = '\0';
        cities[c] = strdup(buffer);
    }
    // Fill array elements with graph_add_edge(g,i,j,k)
    while ((c = fscanf(infile, "%d %d %d\n", &i, &j, &k)) != EOF) {
        if (c != 3) {
            printf("Malformed line\n");
            break;
        }
        graph_add_edge(g, i, j, k);
    }

    // -o outputfile argument call
    // dfs function call is linked with outputfile call because of how
    // the verbose parameter works with the print functions associated with
    // dfs, Stack, and Path.
    if (set_member(args, OUTFILE)) {
        FILE *outfile = fopen(output_file, "w");
        dfs(g, START_VERTEX, curr, shortest, cities, outfile, set_member(args, VERBOSE));
        path_print(shortest, outfile, cities);
        fprintf(outfile, "Total recursive calls: %d\n", count);
    } else {
        dfs(g, START_VERTEX, curr, shortest, cities, stdout, set_member(args, VERBOSE));
        path_print(shortest, stdout, cities);
        fprintf(stdout, "Total recursive calls: %d\n", count);
    }

    // Memory Freedom
    path_delete(&curr);
    path_delete(&shortest);
    graph_delete(&g);
    // Frees names array for cities
    for (int c = 0; c < q; c++) {
        free(cities[c]);
    }
    fclose(outfile);
    fclose(infile);
    return 0;
}

// dfs implementation
void dfs(
    Graph *g, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbo) {

    uint32_t hol;
    graph_mark_visited(g, v);
    path_push_vertex(curr, v, g);

    for (uint32_t w = 0; w < graph_vertices(g); w++) {
        if (path_length(shortest) > 0 && path_length(curr) > path_length(shortest)) {
            break;
        }
        if ((!graph_visited(g, w)) && graph_has_edge(g, v, w)) {
            dfs(g, w, curr, shortest, cities, outfile, verbo);
            graph_mark_unvisited(g, w);

        } else if ((graph_visited(g, w)) && graph_has_edge(g, v, w) && w == START_VERTEX
                   && (path_vertices(curr) == graph_vertices(g))) {
            dfs(g, w, curr, shortest, cities, outfile, verbo);
        }
    }
    if (path_vertices(curr) == (graph_vertices(g) + 1)) {
        if (path_length(curr) < path_length(shortest) || path_length(shortest) == 0) {
            path_copy(shortest, curr);
            if (verbo) {
                path_print(curr, outfile, cities);
            }
        }
    }
    path_pop_vertex(curr, &hol, g);
    count += 1;
}
