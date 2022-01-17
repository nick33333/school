#include "philos.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLAYERS 14
#define DOLLA   3

// The left and right functions return the indices of the left or right player
// These functions were given from the asgn1 pdf
static inline uint32_t left(uint32_t pos, uint32_t players) {
    return ((pos + players - 1) % players);
}
static inline uint32_t right(uint32_t pos, uint32_t players) {
    return ((pos + 1) % players);
}

// This typedef connects the outcome of a dice roll to an LRC action.
// Given from the asgn1 pdf.
typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

// Bank represents the dollar amounts held by all players/philosophers.
// DOLLA corresponds to the starting amount that players are given.
int bank[14] = { DOLLA, DOLLA, DOLLA, DOLLA, DOLLA, DOLLA, DOLLA, DOLLA, DOLLA, DOLLA, DOLLA, DOLLA,
    DOLLA, DOLLA };

// Given two positive integers as input for the seed value to use (seed)
// and number of players starting the game (splayers), the main function carries
// out a simulation of LRC. The numbers of active players, dollars in the
// pot/center, trial/round number and index for a player's turn are assigned to
// the variables aplayer, pot, trial and turn respectively. The outcome of the
// dice which will be randomly generated from random will determine how the game
// of LRC is played out. The output of this function will be a series of print
// statements that correspond to a change or action in LRC as a result of each
// turn's dice roll. Once there is only one player with a dollar amount above
// zero in the bank, a final print statement declares them the winner.
int main() {
    uint32_t aplayers, splayers, pot, trial, turn;
    int seed;
    printf("Random seed: ");
    scanf("%d", &seed);
    if (seed <= 0) {
        fprintf(stderr, "Pseudorandom seed must be non-negative (%d).\n", seed);
        return 0;
    }
    printf("How many players? ");
    // This if statement and fprintf statement were inspired from the code found
    // in a code review held by Professor Long.
    scanf("%u", &splayers);
    if ((splayers < 1) || splayers > PLAYERS) {
        fprintf(stderr, "Number of players  must be from 1 to 14.\n");
        return 0;
    }
    srandom(seed);
    pot = 0;
    for (int c = splayers; c < 14; c++) {
        bank[c] = 0;
    }
    aplayers = splayers;
    for (trial = 0; aplayers > 1; trial++) {
        turn = (trial % splayers);
        if (bank[turn] > 0) {
            printf("%s rolls... ", philosophers[turn]);
            int tmp_bank = 0;
            int allowed_rolls = 0;
            if (bank[turn] >= 3) {
                allowed_rolls = 3;
            } else if (bank[turn] < 3) {
                allowed_rolls = bank[turn];
            }
            for (int d = 0; d < allowed_rolls; d++) {
                int roll = random() % 6;
                if (die[roll] == 0) {
                    printf("gets a pass ");
                } else if (die[roll] == 1) {
                    tmp_bank -= 1;
                    if (bank[turn] + tmp_bank == 0) {
                        aplayers -= 1;
                    }
                    if (bank[left(turn, splayers)] == 0) {
                        aplayers += 1;
                    }
                    bank[left(turn, splayers)] += 1;
                    printf("gives $1 to %s ", philosophers[left(turn, splayers)]);
                } else if (die[roll] == 2) {
                    tmp_bank -= 1;
                    if (bank[turn] + tmp_bank == 0) {
                        aplayers -= 1;
                    }
                    if (bank[right(turn, splayers)] == 0) {
                        aplayers += 1;
                    }
                    bank[right(turn, splayers)] += 1;
                    printf("gives $1 to %s ", philosophers[right(turn, splayers)]);
                } else if (die[roll] == 3) {
                    tmp_bank -= 1;
                    if (bank[turn] + tmp_bank == 0) {
                        aplayers -= 1;
                    }
                    pot += 1;
                    printf("puts $1 in the pot ");
                }
            }
            bank[turn] += tmp_bank;
            printf("\n");
        }
    }
    for (int p = 0; p < 14; p++) {
        if (bank[p] != 0) {
            printf(
                "%s wins the $%d pot with $%d left in the bank!\n", philosophers[p], pot, bank[p]);
        }
    }
    return 0;
}
