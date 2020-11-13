#pragma once 

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;

using namespace std;

enum Type
{
    flight,
    cruise,
    combined
};

struct Date
{
    u16	time;
    u8	day;
    u8	month;
    u8	year;
};
