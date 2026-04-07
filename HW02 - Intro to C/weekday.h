#ifndef WEEKDAY_H
#define WEEKDAY_H

enum day {
    Sunday=1,
    Monday=2,
    Tuesday=3,
    Wednesday=4,
    Thursday=5,
    Friday=6,
    Saturday=7
} day;

void weekday(char* characters, enum day numerical);

#endif