#pragma once

#include <stdint.h>
#include <string>

#include "Types.hpp"

class Ticket
{
protected:
    u16  nr;
    u16  estTime;
    Date date;
    Type type;

    string start;		// starting point
    string destination;		// final destination
public:
    Ticket(u16, u16, Date, Type, string, string);
    virtual ~Ticket() {};

    string getPoint(string);	// "start" or "destination" !
    u16		getNr();
    u16		getType();
    Date	getDate();
    virtual u8	getId() = 0;
};

