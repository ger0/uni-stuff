#include <cstdlib>
#include <cstdio>
#include <utility>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>

const float    DENSITY = 0.3;
unsigned       STEP    = 0;

// ------------------------------------- tasowanie -------------------------
void shuffle(std::vector<unsigned>& arr, unsigned size)
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

// ------------------------------------- generacja -------------------------
void generateGraph(unsigned vertices, unsigned edges, std::vector<std::vector<unsigned>> &arr)
{
   // przypisuje do kazdej krawedzi nastepny wierzcholek 
   for (unsigned i = 0; i < vertices; i++)
   {
      arr[i].push_back((i + 1) % vertices);
      arr[(i + 1) % vertices].push_back(i);
   }

   // pozostale krawedzie do dopisania
   unsigned vertLeft = 0;
   vertLeft = edges - vertices;

   if (int(edges - vertices) < 0)
      vertLeft = 0;

   for (unsigned i = 0; i < vertLeft; i += 2)
   {
      arr[i % vertices].push_back((i + 1) % vertices);
      arr[(i + 1) % vertices].push_back(i % vertices);

      arr[i % vertices].push_back((i + 2) % vertices);
      arr[(i + 2) % vertices].push_back(i % vertices);

      arr[(i + 1) % vertices].push_back((i + 2) % vertices);
      arr[(i + 2) % vertices].push_back((i + 1) % vertices);
   }
}
// -------------------------------------------------------------------------
int main()
{
   unsigned vertices = 15;
   unsigned edges;

   scanf("%u", &vertices);

   std::vector<std::vector<unsigned>> list(vertices);
   edges = DENSITY * (vertices * (vertices - 1) / 2);

   generateGraph(vertices, edges, list);
   /*
   for (unsigned i = 0; i < vertices; i++)
   {
      printf("size %d: %u \n", i, (unsigned)list[i].size());
      if (list[i].size() % 2)
         printf("%u is not even! \n", i);
   }
   */

   std::vector<bool> visited(vertices);
   return 0;
}

