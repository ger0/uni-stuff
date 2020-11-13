#include <cstdio>
#include <iostream>
#include <cinttypes>

#include "Ticket.hpp"
#include "Cruise.hpp"
#include "Flight.hpp"
#include "Combined.hpp"

#include "Types.hpp"
#include "Base.hpp"

template<class T>
bool transfer(u8 id, Base<T>& from, Base<T>& to)
{
    if (from.isAt(id))
    {
	to += from.at(id);
	from -= id;
	return true;
    }
    else
	return false;

}

// reads text data
bool dataLoader(Base<Cruise>* cruises, Base<Flight>* flights, Base<Combined>* combined = NULL)
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

int main()
{
    // baza biletow
    Base<Cruise> cruises;
    Base<Flight> flights;

    // baza biletow zarezerwowane
    Base<Cruise> rvCruise;
    Base<Flight> rvFlight;
    Base<Combined> rvCombined;
   
    if (!dataLoader(&cruises, &flights))
	return -1;

    char input = 0;
    while (input != 'x')
    {

	printf("a) dokonaj rezerwacji\n");
	printf("b) wyswietl zarezerwowane bilety\n");
	printf("c) przestan rezerwowac bilet\n");
	printf("x) wyjdz\n");

	fflush(stdin);
	scanf("%c", &input);
	getchar();

	switch(input)
	{
	    case 'A':
	    case 'a':
	    {
		cruises.draw();
		flights.draw();
		printf("Podaj typ biletu ([Z]wykly, [K]ombinowany, [E] - wyjdz) : ");
		u8 id;

		scanf("%c", &input);
		getchar();

		switch(input)
		{
		    // ZWYKLY
		    case 'Z':
		    case 'z':
		    {
			printf("Podaj id biletu do rezerwacji: \n");

			scanf("%" SCNu8, &id);
			getchar();

			if (!transfer(id, flights, rvFlight) 
			&& !transfer(id, cruises, rvCruise))
			    printf("Wybrany identyfikator nie istnieje w bazie danych!!\n");
			break;
		    }
		    // KOMBINOWANY
		    case 'K':
		    case 'k':
		    {
			while (input != 'E' || input != 'e')
			{
			    printf("Podaj id biletu do rezerwacji: \n");

			    scanf("%" SCNu8, &id);
			    getchar();

			    if (!transfer(id, flights, rvFlight) 
			    && !transfer(id, cruises, rvCruise))
				printf("Wybrany identyfikator nie istnieje w bazie danych!!\n");
			}
			break;
		    }
		    default:
			break;
		}
		break;
	    }
	    case 'B':
	    case 'b':
	    {
		rvCruise.draw();
		rvFlight.draw();
		rvCombined.draw();

		printf("Nacisnij dowolny klawisz...\n");
		getchar();
		break;
	    }
	    case 'C':
	    case 'c':
	    {
		u8 id = 0;
		printf("podaj id biletu ktorego nie chcesz juz rezerwowac: \n");

		scanf("%" SCNu8, &id);
		getchar();
		printf("podany: %u\n", (unsigned)id);

		if (!transfer(id, rvFlight, flights) 
		&& !transfer(id, rvCruise, cruises))
		    printf("Wybrany identyfikator nie istnieje w bazie danych!!\n");
		break;
	    }
	}
    }

    return 0;
}
