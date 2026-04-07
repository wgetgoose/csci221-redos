#include "weekday.h"
#include <stdint.h>

// REDO: Fixed re-definition of enum from header file. Style

// code repition
// i could build a separate function called fill_array,
// but i don't want to deal with returning char*

void weekday(char* characters, enum day numerical) {
    switch (numerical) {
        case 1:
            char mon[10] = "Monday";
            for (uint8_t i = 0; i < 10; i++) {
                characters[i] = mon[i];
            }
            break;
        case 2:
            char tues[10] = "Tuesday";
            for (uint8_t i = 0; i < 10; i++) {
                characters[i] = tues[i];
            }
            break;
        case 3:
            char wed[10] = "Wednesday";
            for (uint8_t i = 0; i < 10; i++) {
                characters[i] = wed[i];
            }
            break;
        case 4:
            char thurs[10] = "Thursday";
            for (uint8_t i = 0; i < 10; i++) {
                characters[i] = thurs[i];
            }
            break;
        case 5:
            char fri[10] = "Friday";
            for (uint8_t i = 0; i < 10; i++) {
                characters[i] = fri[i];
            }
            break;
        case 6:
            char sat[10] = "Saturday";
            for (uint8_t i = 0; i < 10; i++) {
                characters[i] = sat[i];
            }
            break;
        case 7:
            char sun[10] = "Sunday";
            for (uint8_t i = 0; i < 10; i++) {
                characters[i] = sun[i];
            }
            break;
    }
}
