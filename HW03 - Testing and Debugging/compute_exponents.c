#include <stdint.h>
unsigned int f(uint16_t x, uint16_t y) {
    uint16_t r = 1;
    uint16_t s = x;
    while (y > 1) {
        if ((y % 2) >= 1) {
            r = x * r;
        }
        s = s * s;
        y = y / 2;
    }
    return r * s;
}