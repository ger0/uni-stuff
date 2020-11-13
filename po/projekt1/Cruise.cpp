#include "Cruise.hpp"

Cruise::Cruise(u16 _nr, u16 _est, Date _date, Type _type, 
	string strt, string dest, string prov, string cab):
    Ticket(_nr, _est, _date, _type, strt, dest), provider(prov), cabin(cab)
{}

string 	Cruise::getProvider()	{ return provider;	}
string 	Cruise::getCabin()	{ return cabin;		}	
u8 	Cruise::getId()		{ return id;		}
