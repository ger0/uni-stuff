#pragma once

#include <string>

#include "Ticket.hpp"
#include "Types.hpp"

class Flight: public Ticket
{
private:
    string	company;
    u8		seat;
public:
    Flight(u16, u16, Date, Type, 
	string, string, string, u8);

    string	getCompany();
    u8		getSeat();	
};
