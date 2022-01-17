#include "hamming.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "hi:o:"
// encode.c takes data from stdin or a txt file by the byte.
// For each byte received by fgetc, 1 upper and 1 lower nibble
// are extracted and converted into an 8-bit hamming code, with
// the 4 bits corresponding to the upper/lower nibble and the other
// 4 bits being parity bits used for tracking erroneous bit flips.
// Hamming codes are sent to output either through an outfile or stdout.

// Returns the lower nibble of val / in encode.c
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

// Returns the lower nibble of val / in encode.c
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

// Packs two nibbles into a byte / in decode.c
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

// This usage function was inpired from the one given in error.c
static void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A Hamming(8, 4) systematic code generator.\n"
        "\n"
        "USAGE\n"
        "  %s [-h] [-i infile] [-o outfile]\n"
        "\n"
        "OPTIONS\n"
        "  -h             Program usage and help.\n"
        "  -i infile      Input data to encode.\n"
        "  -o outfile     Output of encoded data.\n",
        exec);
}
static FILE *infile;
static FILE *outfile;
static char *input_file;
static char *output_file;

int main(int argc, char **argv) {

    int c = 0;
    char q;
    while ((c = getopt(argc, argv, OPTIONS)) != -1) {
        switch (c) {
        case 'i': input_file = optarg; break;
        case 'o': output_file = optarg; break;
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    // Generator G
    BitMatrix *G = bm_create(4, 8);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == j) {
                bm_set_bit(G, i, j);
            }
            if (j > 3 && (j - 4) != i) {
                bm_set_bit(G, i, j);
            }
        }
    }

    if (input_file) {
        infile = fopen(input_file, "rb");
    } else {
        infile = stdin;
    }
    if (output_file) {
        outfile = fopen(output_file, "wb");
    } else {
        outfile = stdout;
    }
    struct stat statbuf;
    fstat(fileno(infile), &statbuf);
    fchmod(fileno(outfile), statbuf.st_mode);

    if ((infile == NULL) || (outfile == NULL)) {
        printf("Infile or outfile are == NULL\n");
    }

    while ((q = fgetc(infile)) != EOF) {
        uint8_t lo_nib = ham_encode(G, lower_nibble(q));
        uint8_t up_nib = ham_encode(G, upper_nibble(q));
        // uint8_t outbyte = pack_byte(up_nib, lo_nib);
        fputc(lo_nib, outfile);
        fputc(up_nib, outfile);
    }

    bm_delete(&G);
    fclose(infile);
    fclose(outfile);

    return 0;
}
