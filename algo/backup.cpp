#include <cstdlib>
#include <cstdio>
#include <utility>
#include <ctime>
#include <vector>

const unsigned PERCENT = 60;

// ------------------------------------- tasowanie ----------------
void shuffle(int *arr, unsigned size)
{
   if (size > 1)
   {
      srand(time(NULL));
      for (unsigned i = 0; i < size - 1; i++)
      {
         unsigned j = i + rand() / (RAND_MAX / (size - i) + 1);
         std::swap(arr[j], arr[i]);
      }
   }
}

// ------------------------------------- generacja ----------------
void generateGraph(unsigned vertices, unsigned edges,  int arr[])
{
   for (unsigned i = 0; i < vertices * vertices; i++)
      arr[i] = 1;

   // gorna przekatna uzyskuje wartosc 0 aby graf byl acykliczny
   for (unsigned y = 0; y < vertices; y++)
      for (unsigned x = y; x < vertices; x++)
         arr[x + y * vertices] = 0;

   // tworzy losowe krawedzie nasycenie PERCENT% 
   int temp[edges] = {0};

   for (unsigned i = 0; i < unsigned(edges * PERCENT / 100); i++)
      temp[i] = 1;

   shuffle(temp, edges);

   unsigned i = 0;
   for (unsigned y = 1; y < vertices; y++)
   {
      for (unsigned x = 0; x < y; x++)
      {
         arr[x + y * vertices] = temp[i];
         i++;
      }
   }
}

int main()
{
   unsigned vertices;
   unsigned edges;

   scanf("%u", &vertices);
   edges = (vertices * (vertices - 1) / 2);

   int matrix[vertices * vertices] = {1};
   generateGraph(vertices, edges, matrix);

   for (unsigned y = 0; y < vertices; y++)
   {
      for (unsigned x = 0; x < vertices; x++)
         printf("%d ", matrix[x + y * vertices]);
      printf("\n");
   }
   return 0;
}
