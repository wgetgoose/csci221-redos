#include "distance_english_to_metric.h"

double distance_english_to_metric (english_measurements m) {
    // measurements taken from google
    double inches_to_meters = 0.0254;
    double feet_to_meters = 0.3048;
    double yards_to_meters = 0.9144;
    double miles_to_meters = 1609.34;
    double retval = 0;
    retval += (m.inches * inches_to_meters);
    retval += (m.feet * feet_to_meters);
    retval += (m.yards * yards_to_meters);
    retval += (m.miles * miles_to_meters);
    return retval;
}