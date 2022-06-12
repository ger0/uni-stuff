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
    std::vector<string> through;
    std::vector<Cruise>	seqC;
    std::vector<Flight> seqF;
public:
    Combined(u16 _nr, u16 _est, Date _date, Type _type,
	    string strt, string dest);
    void push_back(Flight);
    void push_back(Cruise);

    Flight popF(unsigned i);
    Cruise popC(unsigned i);

    // estimated time, first iterator, last iterator (to vectors)
    void parseInfo(u16 estT, u16 first, u16 last);

    unsigned len(string type);
    void printThrough();
};
