#include "Combined.hpp"

Combined::Combined(u16 _nr, u16 _est, Date _date, Type _type,
	string strt, string dest):
    Ticket(_nr, _est, _date, _type, strt, dest) {}
