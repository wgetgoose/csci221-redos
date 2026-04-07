#include "powers.h"
#include <stdint.h>

// not in header file because this is implementation, not use
// power function
uint8_t p (uint8_t a, uint8_t b) {
    uint8_t retval = 1;
    for (uint8_t i = 0; i < b; i++) {
        retval = retval * a;
    }
    return retval;
}

uint8_t powers (uint8_t x) {
    // two is minimum value per instructions
    uint8_t a = 2;
    uint8_t b = 2;
    uint8_t number_of_pairs = 0;
    while (1) {
        uint8_t a_power_b = p(a, b);
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