#pragma once 

#include "Ticket.hpp"
#include "Flight.hpp"
#include "Cruise.hpp"

#include <string>
#include <vector>

#include "Types.hpp"

class Combined: public Ticket
{
private:
    std::vector<u8>	id;
    std::vector<Cruise>	seqC;
    std::vector<Flight> seqF;
public:
    Combined(u16 _nr, u16 _est, Date _date, Type _type,
	    string strt, string dest);
};
