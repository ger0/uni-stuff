#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 512

int main(int argc, char* argv[])
{
   char buf[MAX];
   char inv[MAX];

   int desc_zrod, desc_cel;
   int lbajt;
   unsigned count = 0;
   size_t size = 0;
 
   if (argc < 2)
   {
      fprintf(stderr, "Za malo argumentow. Uzyj:\n");
      fprintf(stderr, "%s <plik zrodlowy>\n", argv[0]);
      exit(1);
   }

   desc_zrod = open(argv[1], 0640);
   if (desc_zrod == -1){
      perror("Blad otwarcia pliku zrodlowego");
      exit(1);
   }

   // rozmiar pliku
   size = lseek(desc_zrod, 0, SEEK_END);
   lseek(desc_zrod, 0, SEEK_SET);

   while(lbajt = read(desc_zrod, buf, MAX))
   {
      if (lbajt < MAX)
         lseek(desc_cel, 0, SEEK_SET);
      else
         lseek(desc_cel, size - (MAX * (count + 1)), SEEK_SET);
      for (unsigned i = 0; i < lbajt; i++)
         inv[i] = buf[lbajt - (i + 1)];

      if (write(desc_cel, inv, lbajt) == -1)
      {
         perror("Blad zapisu pliku docelowego");
         exit(1);
      }
      count++;
   }
   if (lbajt == -1){
      perror("Blad odczytu pliku zrodlowego");
      exit(1);
   }

   if (close(desc_zrod) == -1 || close(desc_cel) == -1){
      perror("Blad zamkniecia pliku");
      exit(1);
   }

   exit(0);
}

