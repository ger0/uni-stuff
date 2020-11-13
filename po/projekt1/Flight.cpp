#include "Flight.hpp"

Flight::Flight(u16 _nr, u16 _est, Date _date, Type _type, 
	string strt, string dest, string _company, u8 _seat):
    Ticket(_nr, _est, _date, _type, strt, dest), company(_company), seat(_seat)
{}

string	Flight::getCompany()	{ return company;	}
u8	Flight::getSeat()	{ return seat;		}	
u8	Flight::getId()		{ return id;		}
