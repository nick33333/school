#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Sahiti's and Eugene's sections helped we find this regex expression
#define WORD    "[a-zA-Z0-9_]+((-|')?[a-zA-Z0-9_]+)*"
#define OPTIONS "hsmt:f:"
#define KILO    1024

// banhammer.c primarily takes data from a txt file through stdin with help from the provided
// parser.c file. However before parsing in input, banhammer.c reads words and word pairs from
// badspeak.txt and newspeak.txt respectively. These words and word pairs are read in through fscanf
// and are used to populate a Bloom filter and Hashtable. Two linked lists are created to hold
// badspeak and oldspeak words read in from input. This was a design choice inspired from what
// was said in Eugene's sections. After all input is read, a message corresponding to the user's choice
// of words is printed out as well as their possible transgressions ot stdout. There is also an option to
// print out seek and link statistics recorded from each use of banhammer.c.

static bool stato = false;
static bool mtfo = false;
static uint32_t ht_sizing = 10000;
static uint32_t bf_sizing = 1048576;

// This usage function was inpired from the one given in error.c
static void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A word filtering program for the GPRSC.\n"
        "  Filters out and reports bad words parsed from stdin.\n"
        "\n"
        "USAGE\n"
        "  %s [-hsm] [-t size] [-f size]"
        "\n\n"
        "OPTIONS\n"
        "  -h           Program usage and help.\n"
        "  -s           Print program statistics.\n"
        "  -m           Enable move-to-front rule.\n"
        "  -t size      Specify hash table size (default: 10000).\n"
        "  -f size      Specify Bloom filter size (default: 2^20).\n",
        exec);
}

// Function to convert strings to lower case, inspired from example usage of tolower on geeksforgeeks
static char *str_low(char *str) {
    int j = 0;
    char ch;
    while (str[j]) {
        ch = str[j];
        // convert ch to lowercase using toLower()
        str[j] = tolower(ch);

        j++;
    }
    return str;
}

int main(int argc, char **argv) {
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 's': stato = true; break;
        case 'm': mtfo = true; break;
        case 't': ht_sizing = atoi(optarg); break;
        case 'f': bf_sizing = atoi(optarg); break;
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    if (bf_sizing == 0) {
        fprintf(stderr, "Invalid Bloom filter size.\n");
        return EXIT_FAILURE;
    }

    if (ht_sizing == 0) {
        fprintf(stderr, "Invalid hash table size.\n");
        return EXIT_FAILURE;
    }

    FILE *bad;
    FILE *new;
    char char_buf[KILO];
    char char_buff[KILO];
    BloomFilter *bf = bf_create(bf_sizing);
    HashTable *ht = ht_create(ht_sizing, mtfo);

    LinkedList *old_list = ll_create(mtfo);
    LinkedList *bad_list = ll_create(mtfo);

    // Add badspeak words to bf and ht
    bad = fopen("badspeak.txt", "r");
    if (bad == NULL) {
        fprintf(stderr, "Failed to open badspeak.txt\n");
    }
    while (fscanf(bad, "%s", char_buf) == 1) {
        bf_insert(bf, char_buf);
        ht_insert(ht, char_buf, NULL);
    }
    fclose(bad);

    // Add oldspeak words to bf and ht
    // Add newspeak words to ht along with corresponding oldspeak
    new = fopen("newspeak.txt", "r");
    if (new == NULL) {
        fprintf(stderr, "Failed to open newspeak.txt\n");
    }
    while (fscanf(new, "%s %s", char_buf, char_buff) > 0) {
        bf_insert(bf, char_buf);
        ht_insert(ht, char_buf, char_buff);
    }
    fclose(new);

    // Regex parser is inspired by the given parser.c code
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    char *word = NULL;
    while ((word = next_word(stdin, &re)) != NULL) {
        word = str_low(word);
        if (bf_probe(bf, word)) {
            // if bf_probe is true, word is a match in bf, check ht now
            Node *ntmp = ht_lookup(ht, word);
            if (ntmp) {
                // if ht_lookup passed, this node has either OLDSPEAK or BADSPEAK
                // store this word in a linked list
                // void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak)
                if (ntmp->newspeak) {
                    ll_insert(old_list, word, ntmp->newspeak);
                } else {
                    ll_insert(bad_list, word, ntmp->newspeak);
                }
            }
        }
    }

    if (stato) {
        fprintf(stdout, "Seeks: %lu\n", seeks);
        fprintf(stdout, "Average seek length: %f\n", (double) links / seeks);
        fprintf(stdout, "Hash table load: %.6lf%%\n", 100 * (double) ht_count(ht) / ht_size(ht));
        fprintf(stdout, "Bloom filter load: %.6lf%%\n", 100 * (double) bf_count(bf) / bf_size(bf));
    } else {
        if ((ll_length(old_list) > 0) && (ll_length(bad_list) > 0)) { // mixed
            printf("%s", mixspeak_message);
            ll_print(bad_list);
            ll_print(old_list);
        } else if ((ll_length(old_list) > 0) && (ll_length(bad_list) == 0)) { // only old
            printf("%s", goodspeak_message);
            ll_print(old_list);
        } else if ((ll_length(old_list) == 0) && (ll_length(bad_list) > 0)) { // only bad
            printf("%s", badspeak_message);
            ll_print(bad_list);
        }
    }

    ll_delete(&old_list);
    ll_delete(&bad_list);
    clear_words();
    regfree(&re);
    bf_delete(&bf);
    ht_delete(&ht);
    return 0;
}
