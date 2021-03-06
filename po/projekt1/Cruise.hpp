#pragma once

#include <string>

#include "Ticket.hpp"
#include "Types.hpp"

class Cruise: public Ticket
{
private:
    string provider;
    string cabin;
public:
    Cruise(u16 _nr, u16 _est, Date _date, Type _type, 
	string strt, string dest, string prov, string cab);

    string getProvider();
    string getCabin();
    u8     getId();
};
