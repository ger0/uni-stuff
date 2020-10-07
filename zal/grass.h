#include <cstring>
#include <cstdio>
#include <cstdlib>

// liczba traw - zakres A - L
const unsigned AMOUNT = 12;

struct Grass
{
   char     code;
   char     name[12];
   unsigned counter = 0;
   float    freq    = 0;
};

void writeGrasses(Grass*);
void fillGrass(Grass*, size_t, char*, unsigned&);

void drawAll(Grass*, unsigned);
