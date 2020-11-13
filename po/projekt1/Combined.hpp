#pragma once 

#include "Ticket.hpp"
#include <string>
#include <vector>

#include "Types.hpp"

class Combined: public Ticket
{
private:
    std::vector<Ticket*> sequence;
public:
    Combined(u16 _nr, u16 _est, Date _date, Type,
	    string, string);
};
