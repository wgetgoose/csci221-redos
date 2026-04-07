#ifndef ENGLISH_TO_METRIC_H
#define ENGLISH_TO_METRIC_H
#include <stdint.h>

typedef struct english_measurements {
    // REDO: Should be unsigned ints, not doubles
    uint32_t inches;
    uint32_t feet;
    uint32_t yards;
    uint32_t miles;
} english_measurements;

double distance_english_to_metric (english_measurements);

#endif