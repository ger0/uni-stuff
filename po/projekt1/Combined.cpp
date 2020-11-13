#include "Combined.hpp"

Combined::Combined(u16 _nr, u16 _est, Date _date, Type _type,
	string strt, string dest):
    Ticket(_nr, _est, _date, _type, strt, dest) {}

void Combined::push_back(Flight ticket)
{
    through.push_back(ticket.getPoint("destination"));
    seqF.push_back(ticket);
}

void Combined::push_back(Cruise ticket)
{
    through.push_back(ticket.getPoint("destination"));
    seqC.push_back(ticket);
}

void Combined::parseInfo(u16 estT, u16 first, u16 last)
{
    if (seqF.size() > 0)
    {
	if (seqF.front().getNr() == first)
	{
	    nr = seqF.front().getNr();
	    date = seqF.front().getDate();
	    start = seqF.front().getPoint("start");
	}
	if (seqF.back().getNr() == last)
	{
	    destination = seqF.back().getPoint("destination");
	}
    }
    if (seqC.size() > 0)
    {
	if (seqC.front().getNr() == first)
	{
	    nr = seqC.front().getNr();
	    date = seqC.front().getDate();
	    start = seqC.front().getPoint("start");
	}
	if (seqC.back().getNr() == last)
	{
	    destination = seqC.back().getPoint("destination");
	}
    }
    estTime = estT;
}

Flight Combined::popF(unsigned i)
{
    Flight temp = seqF[i];
    return temp;
}
Cruise Combined::popC(unsigned i)
{
    Cruise temp = seqC[i];
    return temp;
}

unsigned Combined::len(string type)
{
    if (type == "Flight")
	return seqF.size();
    else if (type == "Cruise")
	return seqC.size();
    else 
	return 0;
}

void Combined::printThrough()
{
    printf("Przez miasta:[");
    for (unsigned i = 0; i < through.size() - 1; i++)
	printf("%s, ", through[i].c_str());
    printf("]\n");
}
