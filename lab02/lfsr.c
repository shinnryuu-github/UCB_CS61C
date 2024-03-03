#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    unsigned b0 = (*reg >> 0) & 1, b2 = (*reg >> 2) & 1, b3 = (*reg >> 3) & 1, b5 = (*reg >> 5) & 1;
    unsigned bit = b0 ^ b2 ^ b3 ^ b5;
    *reg = (*reg) >> 1;
    *reg = (*reg & ~(1 << 15)) | (bit << 15);
}
