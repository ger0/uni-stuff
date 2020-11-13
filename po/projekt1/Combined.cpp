#include "Combined.hpp"

Combined::Combined(u16 _nr, u16 _est, Date _date, Type _type,
	string strt, string dest):
    Ticket(_nr, _est, _date, _type, strt, dest) {}

void Combined::push_back(Flight ticket)
{
    seqF.push_back(ticket);
}

void Combined::push_back(Cruise ticket)
{
    seqC.push_back(ticket);
}

bool Combined::parseInfo(u16 estT)
{
    if (isDateGreater(seqC.front().getDate(), seqF.front().getDate()))
    {
	nr	= seqC.front().getNr(); 
	estTime = seqC.front().getEstT();
	date 	= seqC.front().getDate();

	start = seqC.front().getPoint("start");

    }
    else
    {
	nr	= seqF.front().getNr(); 
	estTime = seqF.front().getEstT();
	date 	= seqF.front().getDate();

	start = seqF.front().getPoint("start");
    }

    if (isDateGreater(seqF.back().getDate(), seqF.back().getDate()))
	destination = seqF.back().getPoint("destination");
    else
	destination = seqC.back().getPoint("destination");
    estTime = estT;
    return true;
}

Flight Combined::pop()
{
    Flight temp = seqF.back();
    seqF.pop_back();
    return temp;
}

Cruise Combined::pop()
{
}

