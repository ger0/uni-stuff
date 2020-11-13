#pragma once

#include <cstdio>
#include <map>
#include <vector>

#include "Types.hpp"
#include "Ticket.hpp"

template<class T>
class Base
{
private:
    std::map<u8, T> idMap;
public:
    // draws selected elements when arguments provided
    void draw(Date* date = NULL, string* from = NULL)
    {
	if (idMap.size() != 0)
	{
	    if (typeid(T) == typeid(Cruise))
		printf("-- REJSY -----------------------------------------------------------------\n");
	    else if (typeid(T) == typeid(Flight))
		printf("--- LOTY -----------------------------------------------------------------\n");
	    else if (typeid(T) == typeid(Combined))
		printf("-- KOMBINOWANE -----------------------------------------------------------\n");

	    printf("| ID | START         CEL        | CZAS  | DATA \n");
	    for (auto i = idMap.begin(); i != idMap.end(); ++i)
	    {
		if (date != NULL && from != NULL)
		{
		    if (!isDateGreater(*date, i->second.getDate()) && 
			    *from != i->second.getPoint("start"))
		    {
			continue;
		    }
		}

		printf("| %-3u", (unsigned)i->second.getNr());
		printf("| %-10s ->", i->second.getPoint("start").c_str());
		printf(" %-10s ", i->second.getPoint("destination").c_str());
		printf("| %-2.2f ", float(i->second.getDate().time / 100.0)); 
		printf("| %-2u", unsigned(i->second.getDate().day)); 
		printf("-%-2u", unsigned(i->second.getDate().month));
		printf("-%-2ur. |\n", unsigned(i->second.getDate().year));
	    }
	    printf("--------------------------------------------------------------------------\n\n");
	}
    }
    void operator+=(T ticket)
    {
	u8 id = ticket.getNr();
	idMap.insert(std::make_pair(id, ticket));
    }
    void operator-=(u8 id)	{ idMap.erase(id);		}
    T at(u8 id)			{ return idMap.find(id)->second;}
    
    // redundant?
    bool isAt(u8 id)
    {
	if (idMap.find(id) != idMap.end())
	    return true;
	else 
	    return false;
    }
};
