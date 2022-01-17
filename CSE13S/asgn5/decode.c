#include "hamming.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"
// decode.c takes data from stdin or a txt file by the byte.
// For each byte received by fgetc, 1 Hamming code is extracted
// and converted into an error syndrom through bm_from_data and matrix
// multiplication with the transpose of the parity checker matrix.
// Depending on the HAM_STATUS returned from ham_decode, an upper nibble
// and lower nibble hamming code will be packed together and sent to output
// either through outfile or stdout. The verbose command line argument -v will
// print out the statistics collected from running decode.c to stderr.

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
        "  A Hamming(8, 4) systematic code decoder.\n"
        "\n"
        "USAGE\n"
        "  %s [-h] [-v] [-i infile] [-o outfile]\n"
        "\n"
        "OPTIONS\n"
        "  -h             Program usage and help.\n"
        "  -v             Print statistics of decoding to stderr.\n"
        "  -i infile      Input data to decode.\n"
        "  -o outfile     Output of decoded data.\n",
        exec);
}
static FILE *infile;
static FILE *outfile;
static char *input_file;
static char *output_file;
static bool verbo = false;

int main(int argc, char **argv) {

    int c = 0;

    while ((c = getopt(argc, argv, OPTIONS)) != -1) {
        switch (c) {
        case 'i': input_file = optarg; break;
        case 'o': output_file = optarg; break;
        case 'v': verbo = true; break;
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    // Mock Ht
    BitMatrix *Ht = bm_create(8, 4);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j && i < 4) {
                bm_set_bit(Ht, i, j);
            }
            if (i > 3 && (i - 4) == j) {
                bm_set_bit(Ht, i, j);
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
    int q; // using char q will cause an EOF before all instances of char 'o' for
        // some reason
    uint8_t test = 0;
    uint8_t lo = 0;
    uint8_t up = 0;
    uint8_t count = 0;
    double bytes = 0;
    double ham_oks = 0;
    double ham_errs = 0;
    double ham_corrs = 0;

    while ((q = fgetc(infile)) != EOF) {
        if (count % 2 == 0) {
            HAM_STATUS lo_dec = ham_decode(Ht, (uint8_t) q, &test);
            if (lo_dec == HAM_OK) {
                ham_decode(Ht, (uint8_t) q, &lo);
                ham_oks += 1;
            } else if (lo_dec == HAM_CORRECT) {
                ham_decode(Ht, (uint8_t) q, &lo);
                ham_corrs += 1;
            } else if (lo_dec == HAM_ERR) {
                ham_errs += 1;
            }
            bytes += 1;

        } else {
            HAM_STATUS up_dec = ham_decode(Ht, (uint8_t) q, &test);
            if (up_dec == HAM_OK) {
                ham_decode(Ht, (uint8_t) q, &up);
                ham_oks += 1;
            } else if (up_dec == HAM_CORRECT) {
                ham_decode(Ht, (uint8_t) q, &up);
                ham_corrs += 1;
            } else if (up_dec == HAM_ERR) {
                ham_errs += 1;
            }

            uint8_t packed = pack_byte(up, lo);
            fputc(packed, outfile);
            bytes += 1;
        }
        count += 1;
    }

    double err_rate = ham_errs / bytes;

    if (verbo) {
        fprintf(stderr, "Total bytes processed: %.0lf\n", bytes);
        fprintf(stderr, "Uncorrected errors: %.0lf\n", ham_errs);
        fprintf(stderr, "Corrected errors: %.0lf\n", ham_corrs);
        fprintf(stderr, "Error rate: %.6lf\n", err_rate);
    }

    return 0;
}
