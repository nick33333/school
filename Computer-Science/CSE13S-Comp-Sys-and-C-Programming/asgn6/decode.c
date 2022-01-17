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
// decode.c primarily takes data from stdin or a txt file by BLOCK sized buffers.
// The first read call confirms that the input file contains the magic number required
// for all files being processed by decode.c. Files stats are also read in.
// The second read call collects a treedump for reconstructing a huffman tree.
// With the reconstructed tree, we may read in data by buffers of size BLOCK.
// While the number of characters decoded < original file size, we may continue reading
// data bit by bit for huffman tree traversal in the decoding process.
// Decoded messages are written to outfile.

static int infile;
static int outfile;
static char *input_file;
static char *output_file;
static bool verbo = false;

// This usage function was inpired from the one given in error.c
static void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A Huffman decoder.\n"
        "  Decompresses a file using the Huffman coding algorithm.\n"
        "\n"
        "USAGE\n"
        "  %s [-h] [-i infile] [-o outfile]\n"
        "\n"
        "OPTIONS\n"
        "  -h             Program usage and help.\n"
        "  -v             Print compression statistics.\n"
        "  -i infile      Input file to decompress.\n"
        "  -o outfile     Output of decompressed data.\n",
        exec);
}

// Just call read_bit and write_bit in main and
int main(int argc, char **argv) {

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

    ;
    // Initialize header before 1st read call
    Header h;
    read_bytes(infile, (uint8_t *) &h, sizeof(Header));
    uint32_t magic_no = h.magic;
    uint16_t perm = h.permissions;
    uint16_t tree_size_no = h.tree_size;
    uint64_t file_size_no = h.file_size;
    // Confirm presence of magic number
    if (magic_no != MAGIC) {
        fprintf(stderr, "Error: unable to read header.\n");
        return EXIT_FAILURE;
    }
    // Set file permissions
    struct stat file_buf;
    fstat(infile, &file_buf);
    fchmod(outfile, perm);

    // Initialize tree dump array before filling it
    uint8_t buffer[BLOCK];
    uint64_t count = 0;
    uint8_t dump[tree_size_no];

    read_bytes(infile, dump,
        tree_size_no); // Fill dump array with  items from tree dump

    // Rebuild tree and read+decode encoded message data
    Node *root = rebuild_tree(tree_size_no, dump);
    uint8_t bit = 0;
    Node *curr = root;
    while (read_bit(infile, &bit) && (count < file_size_no)) {
        if (bit == 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
        if (leaf_checker(curr)) {
            buffer[count % BLOCK] = curr->symbol;
            count += 1;
            curr = root;
            if (count < file_size_no && (count) % BLOCK == 0) {
                write_bytes(outfile, buffer, BLOCK);
            }
            if (count == file_size_no) {
                write_bytes(outfile, buffer, count % BLOCK);
                break;
            }
        }
    }
    delete_tree(&root);

    if (verbo) {
        fprintf(stderr, "Compressed file size: %lu bytes\n", bytes_read);
        fprintf(stderr, "Decompressed file size: %lu bytes\n", bytes_written);
        fprintf(
            stderr, "Space saving: %.2lf%%\n", 100 * (1 - ((float) bytes_read / bytes_written)));
    }

    close(infile);
    close(outfile);
    return 0;
}
