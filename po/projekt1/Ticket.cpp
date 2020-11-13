#include "Ticket.hpp"

u16 Ticket::getNr()	{ return nr;	}
u16 Ticket::getType()	{ return type;	}
Date Ticket::getDate()	{ return date;	}

Ticket::Ticket(u16 _nr, u16 _est, Date _date, Type _type, 
	std::string strt, std::string dest):
    nr(_nr), estTime(_est), date(_date), type(_type),
    start(std::string(strt)), destination(std::string(dest))
{
}

std::string Ticket::getPoint(std::string point)
{
    if (point == "destination")
	return destination;
    else if (point == "start")
	return start;
    else
    {
	return "0";
    }
}
