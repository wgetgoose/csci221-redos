#include "add_tfp.h"
#include "add_matching_tfp.h"
#include <stdint.h>
#include <stdio.h>

// 0 |     0000     |     000
// s     Exponent       Mantissa

uint8_t shift_and_round(uint8_t* m, uint8_t* exp) {
    // case: number too large
    if (*m > 0b00001111) {
        while (*m > 0b00001111) {
            // if the bit we are shifting off is a 1,
            // and the second least significant bit is a 0,
            // we need to round up
            if ((*m & 0b00000001) == 0b00000001) {
                if ((*m & 0b00000010) == 0b00000010) {
                    break;
                } else {
                    *m = (*m + 0b00000001);
                }
            }
            *m = (*m >> 1);
            *exp = (*exp + 0b00001000);
            continue;
        }
        return 1;
    }
}

void align(uint8_t* exponent_x, uint8_t* mantissa_x, uint8_t* exponent_y, uint8_t* mantissa_y) {
    uint8_t* exponent_to_align;
    uint8_t* mantissa_to_align;
    uint8_t target_alignment;
    if (*exponent_x > *exponent_y) {
        exponent_to_align = exponent_y;
        mantissa_to_align = mantissa_y;
        target_alignment = *exponent_x;
    } else {
        exponent_to_align = exponent_x;
        mantissa_to_align = mantissa_x;
        target_alignment = *exponent_y;
    }
    //printf("Mantissa to align: %08b\n", *mantissa_to_align);
    while (*exponent_to_align != target_alignment) {
        *mantissa_to_align = (*mantissa_to_align >> 1);
        *exponent_to_align = (*exponent_to_align + 0b00001000);
        continue;
    }
}

tfp add_tfp_positive (tfp x, tfp y) {
    typedef enum state {
        same_exponent_normalized,
        diff_exponent_normalized,
        denormalized,
        diff_sign,
        special,
        // mismatch is where one is normalized, the other is not
        mismatch,
    } state;
    // break the tfp's down into their
    // components
    uint8_t exponent_x = (x & 0b01111000);
    uint8_t exponent_y = (y & 0b01111000);
    uint8_t mantissa_x = (x & 0b00000111);
    uint8_t mantissa_y = (y & 0b00000111);
    uint8_t sign_x = (x & 0b10000000);
    uint8_t sign_y = (y & 0b10000000);
    tfp retval = 0;
    state curr_state;
    if ((exponent_x == exponent_y) && (exponent_x != 0)) {
        curr_state = same_exponent_normalized;
    } else if ((exponent_x != exponent_y) && (exponent_x != 0) && (exponent_y != 0)) {
        curr_state = diff_exponent_normalized;
    } else if ((exponent_x == exponent_y) && (exponent_x == 0)) {
        curr_state = denormalized;
    } else if ((exponent_x != exponent_y) && ((exponent_x == 0) || (exponent_y == 0))) {
        curr_state = mismatch;
    }
    switch (curr_state)
    {
    case same_exponent_normalized:
        // i want to "add back" the implicit leading one
        // remember: the dot is 0b00001.XXX
        mantissa_x = (mantissa_x + 0b00001000);
        mantissa_y = (mantissa_y + 0b00001000);
        //printf("Mantissa X: %08b\n", mantissa_x);
        uint8_t retval_mantissa = mantissa_x + mantissa_y;
        //printf("Retval mantissa after addition: %08b\n", retval_mantissa);
        uint8_t retval_exponent = exponent_x;
        shift_and_round(&retval_mantissa, &retval_exponent);
        // only include mantissa bits
        retval_mantissa = (retval_mantissa & 0b00000111);
        retval = sign_x | retval_exponent | retval_mantissa;
        return retval;
    case diff_exponent_normalized:
        mantissa_x = (mantissa_x + 0b00001000);
        mantissa_y = (mantissa_y + 0b00001000);
        align(&exponent_x, &mantissa_x, &exponent_y, &mantissa_y);
        retval_mantissa = mantissa_x + mantissa_y;
        retval_exponent = exponent_x;
        shift_and_round(&retval_mantissa, &retval_exponent);
        retval_mantissa = (retval_mantissa & 0b00000111);
        retval = sign_x | retval_exponent | retval_mantissa;
        return retval;
    case denormalized:
        retval_mantissa = mantissa_x + mantissa_y;
        retval_exponent = exponent_x;
        shift_and_round(&retval_mantissa, &retval_exponent);
        retval = sign_x | retval_exponent | retval_mantissa;
        return retval;
    case mismatch:
        if (exponent_x == 0b00000000) {
            exponent_x = 0b00111000;
            mantissa_y = (mantissa_y + 0b00001000);
            retval_exponent = exponent_y;

        } else {
            exponent_y = 0b00111000;
            mantissa_x = (mantissa_x + 0b00001000);
            retval_exponent = exponent_x;
        }
        align(&exponent_x, &mantissa_x, &exponent_y, &mantissa_y);
        retval_mantissa = mantissa_x + mantissa_y;
        //printf("Retval mantissa after addition: %08b\n", retval_mantissa);
        shift_and_round(&retval_mantissa, &retval_exponent);
        // only include mantissa bits
        retval_mantissa = (retval_mantissa & 0b00000111);
        retval = sign_x | retval_exponent | retval_mantissa;
        return retval;
    }
}

uint8_t shift_and_round_mixed(uint8_t* m, uint8_t* exp) {
    //printf("Initial mantissa %08b, Initial Exponent %08b\n", *m, *exp);
    // case: number too large
    if (*m < 0b00001000) {
        while (*m < 0b00001000) {
            *m = (*m << 1);
            *exp = (*exp - 0b00001000);
            //printf("New mantissa: %08b, New Exponent: %08b\n", *m, *exp);
            continue;
        }
        return 1;
    }
}

tfp add_tfp_mixed (tfp x, tfp y) {
    typedef enum state {
        same_exponent_normalized,
        diff_exponent_normalized,
        denormalized,
        diff_sign,
        special,
        // mismatch is where one is normalized, the other is not
        mismatch,
    } state;
    // break the tfp's down into their
    // components
    uint8_t exponent_x = (x & 0b01111000);
    uint8_t exponent_y = (y & 0b01111000);
    uint8_t mantissa_x = (x & 0b00000111);
    uint8_t mantissa_y = (y & 0b00000111);
    uint8_t sign_x = (x & 0b10000000);
    uint8_t sign_y = (y & 0b10000000);
    tfp retval = 0;
    state curr_state;
    uint8_t bigger_exponent;
    uint8_t smaller_exponent;
    uint8_t bigger_mantissa;
    uint8_t smaller_mantissa;
    uint8_t bigger_sign;
    if (exponent_x > exponent_y) {
        bigger_exponent = exponent_x;
        bigger_mantissa = mantissa_x;
        smaller_exponent = exponent_y;
        smaller_mantissa = mantissa_y;
        bigger_sign = sign_x;
    } else if (exponent_y > exponent_x) {
        bigger_exponent = exponent_y;
        bigger_mantissa = mantissa_y;
        smaller_exponent = exponent_x;
        smaller_mantissa = mantissa_x;
        bigger_sign = sign_y;
    } else {
        if (mantissa_y > mantissa_x) {
            bigger_mantissa = mantissa_y;
            bigger_sign = sign_y;
            bigger_exponent = exponent_y;
            smaller_mantissa = mantissa_x;
            smaller_exponent = exponent_x;
        } else {
            bigger_mantissa = mantissa_x;
            bigger_sign = sign_x;
            bigger_exponent = exponent_x;
            smaller_mantissa = mantissa_y;
            smaller_exponent = exponent_y;
        }
    }
    if ((exponent_x == exponent_y) && (exponent_x != 0)) {
        curr_state = same_exponent_normalized;
    } else if ((exponent_x != exponent_y) && (exponent_x != 0) && (exponent_y != 0)) {
        curr_state = diff_exponent_normalized;
    } else if ((exponent_x == exponent_y) && (exponent_x == 0)) {
        curr_state = denormalized;
    } else if ((exponent_x != exponent_y) && ((exponent_x == 0) || (exponent_y == 0))) {
        curr_state = mismatch;
    }
    switch (curr_state)
    {
    case same_exponent_normalized:
        // i want to "add back" the implicit leading one
        // remember: the dot is 0b00001.XXX
        bigger_mantissa = (bigger_mantissa + 0b00001000);
        smaller_mantissa = (smaller_mantissa + 0b00001000);
        //printf("Mantissa X: %08b\n", mantissa_x);
        uint8_t retval_mantissa = bigger_mantissa - smaller_mantissa;
        //printf("Retval mantissa after addition: %08b\n", retval_mantissa);
        uint8_t retval_exponent = bigger_exponent;
        shift_and_round_mixed(&retval_mantissa, &retval_exponent);
        // only include mantissa bits
        retval_mantissa = (retval_mantissa & 0b00000111);
        retval = bigger_sign | retval_exponent | retval_mantissa;
        return retval;
    case diff_exponent_normalized:
        bigger_mantissa = (bigger_mantissa + 0b00001000);
        smaller_mantissa = (smaller_mantissa + 0b00001000);
        align(&bigger_exponent, &bigger_mantissa, &smaller_exponent, &smaller_mantissa);
        retval_mantissa = bigger_mantissa - smaller_mantissa;
        retval_exponent = bigger_exponent;
        shift_and_round_mixed(&retval_mantissa, &retval_exponent);
        retval_mantissa = (retval_mantissa & 0b00000111);
        retval = bigger_sign | retval_exponent | retval_mantissa;
        return retval;
    case denormalized:
        retval_mantissa = bigger_mantissa - smaller_mantissa;
        retval_exponent = bigger_exponent;
        //shift_and_round_mixed(&retval_mantissa, &retval_exponent);
        retval = bigger_sign | retval_exponent | retval_mantissa;
        return retval;
    case mismatch:
        /* if (exponent_x == 0b00000000) {
            exponent_x = 0b00111000;
            mantissa_y = (mantissa_y + 0b00001000);
            retval_exponent = exponent_y;

        } else {
            exponent_y = 0b00111000;
            mantissa_x = (mantissa_x + 0b00001000);
            retval_exponent = exponent_x;
        } */
        smaller_exponent = 0b00111000;
        bigger_mantissa = (bigger_mantissa + 0b00001000);
        retval_exponent = bigger_exponent;
        align(&bigger_exponent, &bigger_mantissa, &smaller_exponent, &smaller_mantissa);
        retval_mantissa = bigger_mantissa - smaller_mantissa;
        //printf("Retval mantissa after addition: %08b\n", retval_mantissa);
        shift_and_round_mixed(&retval_mantissa, &retval_exponent);
        // only include mantissa bits
        retval_mantissa = (retval_mantissa & 0b00000111);
        retval = bigger_sign | retval_exponent | retval_mantissa;
        return retval;
    }
}

tfp add_tfp(tfp x, tfp y) {
    if ((x & 0b10000000) != (y & 0b10000000)) {
        add_tfp_mixed(x, y);
    } else {
        return add_tfp_positive(x, y);
    }
}