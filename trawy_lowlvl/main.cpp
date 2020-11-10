#include "grass.h"

char* readFile(const char* filename, size_t& size)
{
   FILE* f = fopen(filename, "r");

   if (f == nullptr)
   {
      printf("Nieudany odczyt\n");
      return NULL;
   }
   if (fseek(f, 0, SEEK_END) != 0)
   {
      printf("Zly rozmiar\n");
      return NULL;
   }
   // obliczanie rozmiaru danych
   size = ftell(f);
   // powrot do poczatku pliku
   rewind(f);
   char* buff = (char*)malloc(size);
   if (buff == NULL)
   {
      printf("Problem z alokacja pamieci\n");
      return NULL;
   }

   size_t read_size = fread(buff, 1, size, f);
   if (size != read_size)
   {
      printf("Rozmiar wczytanego pliku niezgodny z oczekiwanym\n");
      return NULL;
   }
   fclose(f);

   return buff;
}

int main()
{
   // inicjalizowanie traw
   Grass grasses[AMOUNT];
   writeGrasses(grasses);
   size_t size = 0;
   char* buff = readFile("trawy.txt", size);

   if (buff == NULL)
      return -1;

   // laczna suma traw
   unsigned amount = 0;
   // wykonywanie zadania
   fillGrass(grasses, size, buff, amount);
   drawAll(grasses, amount);

   free(buff);
   return 0;
}
