#include "main.h"
#include "choose_mover.h"
#include "powers.h"
#include "distance_english_to_metric.h"
#include <stdio.h>
#include <stdlib.h>

int main (void) {
    // Test choose_mover
    uint8_t moving_boxes = 100;
    char alice_or_bob = choose_mover(moving_boxes);
    printf("Alice or Bob for %d boxes: %c\n", moving_boxes, alice_or_bob);
    // Test powers
    uint8_t test_value = 18;
    uint8_t test_result = powers(test_value);
    printf("Powers of %d: %d\n", test_value, test_result);
    // test distance
    english_measurements test_struct;
    test_struct.feet = 100;
    test_struct.inches = 0;
    test_struct.miles = 2;
    test_struct.yards = 0;
    double distance = distance_english_to_metric(test_struct);
    printf("%u feet and %u miles to meters: %f\n", test_struct.feet,
            test_struct.miles, distance);
    // not including anything for weekday, because it returns void
    // and i will get yelled at by gcc for unused declaration
}