#include "powers.h"
#include <stdint.h>

// not in header file because this is implementation, not use
// power function

// REDO: Larger integers
uint32_t p (uint32_t a, uint32_t b) {
    uint32_t retval = 1;
    for (uint32_t i = 0; i < b; i++) {
        retval = retval * a;
    }
    return retval;
}

uint32_t powers (uint32_t x) {
    // two is minimum value per instructions
    uint32_t a = 2;
    uint32_t b = 2;
    uint32_t number_of_pairs = 0;
    while (1) {
        uint32_t a_power_b = p(a, b);
        // iterative condition
        if (a_power_b <= x) {
            number_of_pairs++;
            b++;
            continue;
        }
        if (a_power_b > x) {
            // if the next iteration (2^3 --> 3^2) also bigger than x
            // exit condition
            if ((p((a+1), 2)) > x) {
                return number_of_pairs;
            } else {
                a++;
                b = 2;
                continue;
            }
        }
    }
}