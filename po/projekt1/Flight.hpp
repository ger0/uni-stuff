#pragma once

#include <string>

#include "Ticket.hpp"
#include "Types.hpp"

using namespace std;

class Flight: public Ticket
{
private:
    string	company;
    u8		seat;
    u8		id;
public:
    Flight(u16, u16, Date, Type, 
	string, string, string, u8);

    string	getCompany();
    u8		getSeat();	
    u8    	getId();
};
