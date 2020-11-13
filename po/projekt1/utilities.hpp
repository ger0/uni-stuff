#pragma once
#include <cstdio>
#include <cinttypes>

#include "Ticket.hpp"
#include "Cruise.hpp"
#include "Flight.hpp"
#include "Combined.hpp"

#include "Types.hpp"
#include "Base.hpp"

// reads text data
inline bool dataLoader(Base<Cruise>* cruises, Base<Flight>* flights, 
	Base<Combined>* combined = NULL)
{
    // buffering data
    Date date; 

    unsigned id, est, time;
    unsigned tDay, tMonth, tYear;
    
    char typ;
    char strStart[16];
    char strDest[16];

    char comName[8];
    char comPlac[4];
    unsigned comSeat;

    // all possible tickets loaded from the file "database.txt"
    FILE* pFile;
    pFile = fopen("database.txt", "r");
    if (pFile == NULL)
	return false;
    else 
    {
	while (!feof(pFile))
	{
	    // ----------- ID | TYP | OD | DO | GODZ | CZAS TRWANIA | DATA(3) --------------
	    fscanf(pFile, "%u %c %s %s %u ", &id, &typ, strStart, strDest, &time);
	    fscanf(pFile, "%u %u %u %u", &est, &tDay, &tMonth, &tYear);
	    // -- provider / company --
	    fscanf(pFile, "%s ", comName);

	    date.time = (u16)time;
	    date.day = (u8)tDay;
	    date.month = (u8)tMonth;
	    date.year = (u8)tYear;

	    if (id == 0)
		return true;

	    switch(typ)
	    {
		case 'X':
		case 'c':
		{
		    fscanf(pFile, "%s", comPlac);
		    *cruises += Cruise((u16)id, (u16)est, date, cruise, 
				    string(strStart), string(strDest), 
				    string(comName), string(comPlac));
		    break;
		}
		case 'f':
		{
		    fscanf(pFile, "%u", &comSeat);
		    *flights += Flight((u16)id, (u16)est, date, flight, 
				    string(strStart), string(strDest), 
				    string(comName), u8(comSeat));
		    break;
		}
	    }
	}
	fclose(pFile);
    }
    return true;
}
