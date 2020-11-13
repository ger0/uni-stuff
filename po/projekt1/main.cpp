#include <cstdio>
#include <iostream>
#include <cinttypes>

#include "Ticket.hpp"
#include "Cruise.hpp"
#include "Flight.hpp"
#include "Combined.hpp"

#include "Types.hpp"
#include "Base.hpp"

bool dataLoader(Base<Cruise>* cruises, Base<Flight>* flights, Base<Combined>* combined = NULL)
{
    // buffering data
    Date data; 

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
	    // ---------------- seat/cabin | provicer/company ------------------------------
	    fscanf(pFile, "%s ", comName);

	    data.time = (u16)time;
	    data.day = (u8)tDay;
	    data.month = (u8)tMonth;
	    data.year = (u8)tYear;

	    if (id == 0)
		return true;

	    else if (typ == 'c')
	    {
		fscanf(pFile, "%s", comPlac);
		*cruises += Cruise((u16)id, (u16)est, data, cruise, 
				string(strStart), string(strDest), 
				string(comName), string(comPlac));
	    }
	    else if (typ == 'f')
	    {
		fscanf(pFile, "%u", &comSeat);
		*flights += Flight((u16)id, (u16)est, data, flight, 
				string(strStart), string(strDest), 
				string(comName), u8(comSeat));
	    }
	    else if (typ == 'X' && combined != NULL)
	    {

	    }	
	}
	fclose(pFile);
    }
    return true;
}

int main()
{
    Base<Cruise> cruises;
    Base<Flight> flights;

    Base<Cruise> rvCruise;
    Base<Flight> rvFlight;
   
    if (!dataLoader(&cruises, &flights))
	return -1;

    char input = 0;

    while (input != 'x')
    {
	printf("\n\na) dokonaj rezerwacji\n");
	printf("b)   \nx) wyjdz\n");

	scanf("%c", &input);
	getchar();

	if (input == 'a')
	{
	    cruises.draw();
	    flights.draw();
	    printf("Podaj typ biletu ([L]ot, [R]ejs, [K]ombinowany, X - wyjdz) : ");
	    u8 id;

	    scanf("%c", &input);
	    getchar();

	    if (input == 'L' || input == 'R' || input == 'K')
	    {
		printf("Podaj id biletu do rezerwacji: \n");

		scanf("%" SCNu8, &id);
		getchar();

		if (input == 'L')
		{
		    rvFlight += flights.at(id);
		    flights  -= id; 
		}
		else if (input == 'R')
		{
		    rvCruise += cruises.at(id);
		    cruises  -= id; 
		}
	    }
	    else if (input == 'X')
		break;
	}
	else if (input == 'b')
	{
	    printf("----------------- ZAREZERWOWANE ---------------------------------------------\n");
	    rvCruise.draw();
	    rvFlight.draw();

	    printf("Nacisnij dowolny klawisz...\n");
	    getchar();
	}
    }

    return 0;
}
