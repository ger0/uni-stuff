#pragma once 

#include <stdint.h>
#include <ctime>

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

inline bool isDateGreater(Date x, Date y)
{
    if (y.year > x.year)
	return true;

    else if (y.year == x.year)
    {
	if (y.month > x.month)
	    return true;

	else if (y.month == x.month)
	{
		if (y.day > x.day)
		    return true;

		else if (y.day == x.day)
		{
		    if (y.time > x.time)
			return true;
		}
	}
    }
    return false;
}

// calculates time after estimated time
//
// CZAS !!!! zamienic Date na std::tm pozniej !!!
inline Date calculateDate(Date* before, u16 hours)
{
    std::tm t = {};
    t.tm_hour = int(before->time);
    t.tm_year = int(before->year) + 100;
    t.tm_mon  = int(before->month) - 1;
    t.tm_mday = int(before->day);

    t.tm_hour += hours;
    std::mktime(&t);

    return {static_cast<u16>(t.tm_hour), static_cast<u8>(t.tm_mday),
	static_cast<u8>(t.tm_mon), static_cast<u8>(t.tm_year - 100)};
}
