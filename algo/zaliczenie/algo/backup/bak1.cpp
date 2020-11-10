#include <cstdlib>
#include <cstdio>
#include <utility>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>

const float    DENSITY = 0.3;

std::vector<unsigned> C;
std::vector<unsigned> V;

bool done = false;

// ------------------------------------- HAMILTON --------------------------
void hamilton(unsigned& v, unsigned& vertices, std::vector<std::vector<unsigned>> &arr)
{
   if (done)
      return;

   V.push_back(v);
   for (unsigned i = 0; i < arr[v].size(); i++)
   {
      unsigned w = arr[v][i];

      bool exists = false;
      for (unsigned j = 0; j < V.size(); j++)
      {
         if (w == V[j])
         {
            exists = true;
            break;
         }
      }

      if (!exists)
         hamilton(w, vertices, arr);
      if (done)
         return;
   }
   if (V.size() == vertices)
   {
      done = true;
   }
   else
   {
      if (v != V.back())
         printf("OH NONONONO\n");
      V.pop_back();
   }
}
// ------------------------------------- EULER -----------------------------
void euler(unsigned& v, unsigned& vertices, std::vector<std::vector<unsigned>> &arr)
{
   while (!arr[v].empty())
   {
      unsigned w = arr[v].back();
      arr[v].pop_back();
      for (unsigned i = 0; i < arr[w].size(); i++)
      {
         if (arr[w][i] == v)
         {
            arr[w].erase(arr[w].begin() + i);
            break;
         }
      }
      euler(w, vertices, arr);
   }
   C.push_back(v);
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
   unsigned poczatek, krok, ilosc;
   printf("GESTOSC: %f\n", DENSITY);
   printf("poczatkowa: ");
   scanf("%u", &poczatek);

   printf("krok: ");
   scanf("%u", &krok);

   printf("ilosc: ");
   scanf("%u", &ilosc);

   auto before = std::chrono::steady_clock::now();
   auto after = std::chrono::steady_clock::now();
   std::chrono::duration<double, std::milli> duration;

   for (unsigned vertices = poczatek; vertices < poczatek + (ilosc * krok); vertices += krok)
   {
      unsigned edges;

      std::vector<std::vector<unsigned>> list(vertices);
      std::vector<std::vector<unsigned>> listH(vertices);
      edges = DENSITY * (vertices * (vertices - 1) / 2);

      generateGraph(vertices, edges, list);

      unsigned v = 0;

      std::copy(list.begin(), list.end(), listH.begin());

      before = std::chrono::steady_clock::now();
      euler(v, vertices, list);
      after = std::chrono::steady_clock::now();
      duration = after - before;

      printf("%u;%f;", vertices, duration.count());
      
      before = std::chrono::steady_clock::now();
      hamilton(v, vertices, listH);
      after = std::chrono::steady_clock::now();
      duration = after - before;

      printf("%f;", duration.count());
      printf("\n");
   }
   return 0;
}

