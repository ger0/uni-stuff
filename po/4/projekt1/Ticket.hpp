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
    Ticket(u16 _nr, u16 _est, Date _date, Type _type, string strt, string dest);
    virtual ~Ticket() {};
    virtual void printThrough();

    string getPoint(string);	// "start" or "destination" !
    u16		getNr();
    u16		getType();
    u16		getEstT();
    Date	getDate();
};

