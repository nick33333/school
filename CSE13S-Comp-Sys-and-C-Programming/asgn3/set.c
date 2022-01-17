#include "set.h"

// This set.c code was taken from the cse13s-resources repo.
// We have been given permission to use it for asgn3.

Set set_empty(void) {
    return 0x00000000; // Empty set is 0s for each bit.
}

bool set_member(Set s, int x) {
    return s
           & (1 << (x
                    % SET_CAPACITY)); // function takes in set and set item, returns bool if item was found in set
}

Set set_insert(Set s, int x) {
    return s | (1 << (x % SET_CAPACITY)); // function takes in set and set item, adds item to set
}

Set set_remove(Set s, int x) {
    return s & ~(1 << (x % SET_CAPACITY));
}

Set set_union(Set s, Set t) {
    return s | t;
}

Set set_intersect(Set s, Set t) {
    return s & t;
}

Set set_difference(Set s, Set t) {
    return s & ~t;
}

Set set_complement(Set s) {
    return ~s;
}
