#ifndef __HELPER_H__
#define __HELPER_H__

#include "code.h"
#include "defines.h"
#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool leaf_checker(Node *n);

int byte_cal(uint32_t bits);

void set_bit(uint8_t buffer[], uint32_t i);

void clr_bit(uint8_t buffer[], uint32_t i);

uint8_t get_bit(uint8_t buffer[], uint32_t i);

void code_set_bit(Code *c, uint32_t i);

void code_clr_bit(Code *c, uint32_t i);

uint8_t code_get_bit(Code *c, uint32_t i);

#endif
