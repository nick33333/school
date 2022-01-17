#include "code.h"
#include "defines.h"
#include "header.h"
#include "helper.h"
#include "huffman.h"
#include "io.h"
#include "pq.h"
#include "stack.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"
// encode.c primarily takes data from stdin or a txt file BLOCK sized buffers.
// This huffman coding algorithm requires 2 reading passes.
// The 1st pass collect data to form a histogram of ascii character frequencies.
// The Header struct holding file stats and a huffman tree dump are written to outfile.
// The 2nd pass reads the contents of infile by BLOCKs and writes codes
// corresponding to each character in the contents to outfile.

static uint64_t histo[ALPHABET];
static uint32_t unicount;
static Code table[ALPHABET];
static int infile;
static int outfile;
static char *input_file;
static char *output_file;
static bool verbo = false;

// This usage function was inpired from the one given in error.c
static void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A Huffman encoder.\n"
        "  Compresses a file using the Huffman coding algorithm.\n"
        "\n"
        "USAGE\n"
        "  %s [-h] [-i infile] [-o outfile]\n"
        "\n"
        "OPTIONS\n"
        "  -h             Program usage and help.\n"
        "  -v             Print compression statistics.\n"
        "  -i infile      Input file to compress.\n"
        "  -o outfile     Output of compressed data.\n",
        exec);
}

void tree_dumper(Node *root, uint8_t treedump[], int *dumpidx);

int main(int argc,
    char **argv) // Just call read_bit and write_bit in main and
// flush_codes, NO BUFFER SHOULD BE INITIALIZED HERE
{

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': input_file = optarg; break;
        case 'o': output_file = optarg; break;
        case 'v': verbo = true; break;
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }
    if (input_file) {
        infile = open(input_file, O_RDONLY);
    } else {
        infile = 0;
    }
    if (output_file) {
        outfile = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    } else {
        outfile = 1;
    }

    struct stat file_buf;
    fstat(infile, &file_buf);
    fchmod(outfile, file_buf.st_mode);

    // 1st read pass for histo counts
    uint8_t buffer[BLOCK];
    int length = 0;

    while ((length = read_bytes(infile, buffer, BLOCK))) {
        for (int i = 0; i < length; i++) {
            // build histogram here
            histo[buffer[i]] += 1;
        }
    }

    if (histo[0] == 0) {
        histo[0] += 1;
    }
    if (histo[255] == 0) {
        histo[255] += 1;
    }

    for (int i = 0; i < ALPHABET; i++) {
        if (histo[i] > 0) { // counts up unicount
            unicount += 1;
        }
    }

    // // Build root of huffman tree
    Node *o = build_tree(histo);

    build_codes(o, table); // table[character] should be enough to generate a code
    // Header stuff
    Header h;
    h.magic = MAGIC; // same
    h.permissions = file_buf.st_mode; // same
    h.tree_size = (3 * unicount) - 1;
    h.file_size = file_buf.st_size; // same
    // Write out header
    write_bytes(outfile, (uint8_t *) &h, sizeof(Header));
    // Initialize tree dump array and fill it
    uint8_t treedump[h.tree_size];
    int dumpidx = 0;
    tree_dumper(o, treedump, &dumpidx);
    write_bytes(outfile, treedump, h.tree_size * sizeof(uint8_t));
    // dump_tree() somewhere before lseek
    // 2nd read pass for printing codes
    lseek(infile, 0, SEEK_SET);
    bytes_read = 0;
    // 2nd pass for reading characters and writing codes
    while ((length = read_bytes(infile, buffer, BLOCK))) {
        for (int i = 0; i < length; i++) { // for symbol in infile , loop write_code
            write_code(outfile, &table[buffer[i]]);
        }
    }
    flush_codes(outfile);

    if (verbo) {
        fprintf(stderr, "Uncompressed file size: %lu bytes\n", bytes_read);
        fprintf(stderr, "Compressed file size: %lu bytes\n", bytes_written);
        fprintf(
            stderr, "Space saving: %.2lf%%\n", 100 * (1 - ((float) bytes_written / bytes_read)));
    }

    delete_tree(&o);
    close(infile);
    close(outfile);
    return 0;
}

void tree_dumper(Node *root, uint8_t treedump[], int *dumpidx) {
    if (root != NULL) {
        tree_dumper(root->left, treedump, dumpidx);
        tree_dumper(root->right, treedump, dumpidx);
        if (root->left == NULL && root->right == NULL) {
            treedump[*dumpidx] = 'L';
            *dumpidx += 1;
            treedump[*dumpidx] = root->symbol;
            *dumpidx += 1;
        } else {
            treedump[*dumpidx] = 'I';
            *dumpidx += 1;
        }
    }
}
