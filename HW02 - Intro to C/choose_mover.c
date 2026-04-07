#include <stdint.h>
#include "choose_mover.h"
//#include <stdio.h>

char choose_mover(uint16_t number_of_boxes) {
    uint16_t alice_rate = 200;
    uint16_t alice_capacity = 23;
    uint16_t alice_number_of_truckloads = 0;
    uint16_t alice_cost = 0;
    // if there exists a remainder, we need to "round up"
    if (number_of_boxes % alice_capacity != 0) {
        alice_number_of_truckloads = (number_of_boxes / alice_capacity) + 1;
        alice_cost = alice_rate * alice_number_of_truckloads;
        //printf("Alice Cost: %u\n", alice_cost);
    }
    // REDO: Fixed incorrect rate for Bob
    uint16_t bob_rate = 260;
    uint16_t bob_capacity = 26;
    uint16_t bob_number_of_truckloads = 0;
    uint16_t bob_cost = 0;
    // if there exists a remainder, we need to "round up"
    if (number_of_boxes % bob_capacity != 0) {
        bob_number_of_truckloads = (number_of_boxes / bob_capacity) + 1;
        bob_cost = bob_rate * bob_number_of_truckloads;
        //printf("Bob Cost: %u\n", bob_cost);
    }
    if (alice_cost <= bob_cost) {
        return 'A';
    } else {
        return 'B';
    }
}
