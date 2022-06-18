#include "grass.h"

void writeGrasses(Grass* grasses)
{
   const char* names[] = {"grzebienica", "izgrzyca", "kostrzewa", "kupkowka", "mietlica", "ostnica", "perz", "rajgras", "stoklosa", "tymotka", "wiechlina", "zycica"};
   for (unsigned i = 0; i < AMOUNT; i++)
   {
      grasses[i].code = char(unsigned('A') + i);
      strcpy(grasses[i].name, names[i]);
   }
}
// wypelnianie licznika traw
void fillCounter(Grass* grasses, size_t size, char* buff, unsigned &amount)
{
   // wypelnianie iloscia wystapien
   unsigned temp = 0;
   for (size_t i = 0; i < size; i++)
   {
      temp = unsigned(buff[i]) - unsigned('A');
      if (temp < AMOUNT)
      {
         amount++;
         grasses[temp].counter++;
      }
   }
}
// wypelnianie czestotliwosci wystepowania traw
void fillFreq(Grass* grasses, unsigned &amount)
{
   for (unsigned i = 0; i < AMOUNT; i++)
   {
      if (amount != 0)
         grasses[i].freq = float(grasses[i].counter) * 100 / float(amount);
      else 
         grasses[i].freq = 0.0; 
   }
}
// wypelnianie struktury
void fillGrass(Grass* grasses, size_t size, char* buff, unsigned& amount)
{
   fillCounter(grasses, size, buff, amount);
   fillFreq(grasses, amount);
}
