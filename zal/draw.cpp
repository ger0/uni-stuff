#include "grass.h"

void drawTable(Grass* grasses, unsigned allAmount)
{
   printf("\n+-----+---------------+-------------+-------------+\n");
   printf(  "| KOD | NAZWA GATUNKU | L.WYSTAPIEN | %% WYSTAPIEN |\n");
   printf(  "+-----+---------------+-------------+-------------+\n");
   for (unsigned i = 0; i < AMOUNT; i++)
   {
      fprintf(stdout, "|  %-3c", grasses[i].code);
      fprintf(stdout, "|   %-12s", grasses[i].name);
      fprintf(stdout, "|     %-8u", grasses[i].counter);
      fprintf(stdout, "|     %-8.2f|", grasses[i].freq);
      printf("\n+-----+---------------+-------------+-------------+\n");
   }
   if (allAmount != 0)
      fprintf(stdout, "|RAZEM|               |     %-8u|     100.00  |", allAmount);
   else
      fprintf(stdout, "|RAZEM|               |     %-8u|     0.00    |", allAmount);
   printf("\n+-----+---------------+-------------+-------------+\n");
}
void drawBar(Grass* grasses)
{
   float    scale = 1;
   unsigned maxi  = 0;

   for (unsigned i = 0; i < AMOUNT; i++)
      if (unsigned(grasses[i].freq) > maxi)
         maxi = unsigned(grasses[i].freq);

   // scale odpowiada za to ze wysokosc slupka zawsze = 25
   scale = 25.f / float(maxi);
   maxi = unsigned(scale * float(maxi));

   printf("\n");
   for (unsigned i = maxi; i > 0; i--)
   {
      for (unsigned j = 0; j < AMOUNT; j++)
      {
         if (unsigned(scale * grasses[j].freq) >= i)
            printf(" ** ");
         else
            printf("    ");
      }
      printf("\n");
   }
   for (unsigned i = 0; i < AMOUNT; i++)
      printf("----");

   printf("\n");

   for (unsigned i = 0; i < AMOUNT; i++)
      printf(" %c  ", grasses[i].code);
   printf("\n");
}
void drawRib(Grass* grasses)
{
   float    scale = 1;
   unsigned maxi  = 0;

   for (unsigned i = 0; i < AMOUNT; i++)
      if (unsigned(grasses[i].freq) > maxi)
         maxi = unsigned(grasses[i].freq);

   // scale odpowiada za to ze szerokosc wstegi zawsze = 50
   scale = 50.f / float(maxi);
   maxi = unsigned(scale * float(maxi));

   printf("\n");
   for (unsigned j = 0; j < AMOUNT; j++)
   {
      printf("%c | ", grasses[j].code);
      for (unsigned i = 0; i < unsigned(grasses[j].freq * scale); i++)
         printf("*");
      printf("\n  |\n");
   }
}

// rysowanie wykresu
void drawAll(Grass* grasses, unsigned amount)
{
   drawTable(grasses, amount);
   drawRib(grasses);
   drawBar(grasses);
}
