#include "io.h"

#include "defines.h"
#include "helper.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Eugene's and Sahiti's sections and pseudocode helped me put together the I/O module a lot.
// The I/O module handles calls to read and write for encode and decode.

static uint8_t bitbuf[BLOCK]; // buffer is full if the number of bits in buffer == BLOCK*8
static uint32_t bitind = 0; // buffer index, units are bits, full if bitind == BLOCK*8
uint64_t bytes_read;
uint64_t bytes_written;

int read_bytes(int infile, uint8_t *buf, int nbytes) { // if nbytes>infile
    int tot_bytes = 0; // total bytes read so far, subract this from nbytes
    int bytes = 0; // whatever read returns, keeps track of bytes read by 1 call of read
    do {
        bytes = read(infile, buf, nbytes - tot_bytes);
        tot_bytes += bytes;

    } while ((bytes > 0) && (tot_bytes != nbytes));

    bytes_read += (uint64_t) tot_bytes;
    return tot_bytes;
}

int write_bytes(int outfile, uint8_t *buf,
    int nbytes) { // Only called when you have a full buffer
    int tot_bytes = 0; // total bytes written so far, subract this from nbytes
    int bytes = 0; // whatever read returns, keeps track of bytes read by 1 call of read
    do {
        bytes = write(outfile, buf, nbytes - tot_bytes);
        tot_bytes += bytes;
    } while ((bytes > 0) && (tot_bytes != nbytes));

    bytes_written += (uint64_t) tot_bytes;
    // printf("Total bytes written: %lu\n",bytes_written);
    return tot_bytes;
}

bool read_bit(int infile, uint8_t *bit) { // calls read_bytes
    // if buffer empty, fill it
    // pass back this bit
    // return if a valid bit was returned
    // need to keep track of end of the buffer
    int lastbit = 0;
    if (bitind == 0) {
        int bytesread = read_bytes(infile, bitbuf,
            BLOCK); // returns result of "I either read a whole block or didn't"
        if (bytesread < BLOCK) {
            lastbit = (bytesread * 8) + 1;
        }
    }
    *bit = get_bit(bitbuf, bitind);
    bitind += 1;
    if (bitind == 8 * BLOCK) {
        bitind = 0;
    }
    if (bitind != 0 && bitind == (uint32_t) lastbit) {
        return false;
    } else {
        return true;
    }
}

void write_code(int outfile, Code *c) { // calls write_bytes
    // buffer each bit of code
    // if buffer is full, write buffer out
    for (uint32_t i = 0; i < code_size(c); i++) {
        if (code_get_bit(c, i) == 1) {
            set_bit(bitbuf, bitind);
        } else {
            clr_bit(bitbuf, bitind);
        }
        bitind += 1;
        if (bitind == 8 * BLOCK) {
            write_bytes(outfile, bitbuf, BLOCK);
            bitind = 0;
        }
    }
}

void flush_codes(int outfile) { // Call flush to get rid of bytes smaller than
    // the size of the buffer but still inside it
    if (bitind > 0) { // if bitind > 0 we must have some bits we need to write out
        write_bytes(outfile, bitbuf, byte_cal(bitind));
    }
}
