#include <cstdlib>
#include <cstdio>
#include <utility>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>

const unsigned PERCENT = 60;
unsigned       STEP    = 0;

// ------------------------------------- tasowanie -------------------------
void shuffle(std::vector<int>& arr, unsigned size)
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
void generateGraph(unsigned vertices, unsigned edges, std::vector<int>& arr, 
                   std::vector<std::vector<int>>& incarr)
{
   for (unsigned i = 0; i < vertices * vertices; i++)
      arr[i] = 1;

   // gorna przekatna uzyskuje wartosc 0 aby graf byl acykliczny
   for (unsigned y = 0; y < vertices; y++)
      for (unsigned x = y; x < vertices; x++)
         arr[x + y * vertices] = 0;

   // tworzy losowe krawedzie nasycenie PERCENT% 
   std::vector<int> temp(edges);
   for (unsigned i = 0; i < unsigned(edges * PERCENT / 100); i++)
      temp[i] = 1;

   shuffle(temp, edges);

   unsigned i = 0;
   for (unsigned y = 1; y < vertices; y++)
   {
      for (unsigned x = 0; x < y; x++)
      {
         arr[x + y * vertices] = temp[i];
         if (temp[i])
            incarr[x].push_back(y);
         i++;
      }
   }
}
// -------------------------------------------------------- DFS ------------
void dfsMatrix(unsigned x, unsigned vertices, std::vector<int>& arr, 
               std::vector<bool>& visited, std::vector<unsigned>& output)
{
   for (unsigned i = 0; i < vertices; i++)
   {
      if (arr[x + i * vertices])
      {
         if (visited[i] == false)
         {
            visited[i] = true;
            dfsMatrix(i, vertices, arr, visited, output);
         }
      }
   }

   STEP++;
   output.insert(output.begin(), x);
}

void dfsList(unsigned x, unsigned vertices, std::vector<std::vector<int>>& arr, 
               std::vector<bool>& visited, std::vector<unsigned>& output)
{
   std::vector<int>& stack = arr[x];
   
   for (unsigned i = 0; i < stack.size(); i++)
   {
      if (visited[stack[i]] == false)
      {
         visited[stack[i]] = true;
         dfsList(stack[i], vertices, arr, visited, output);
      }
   }

   STEP++;
   output.insert(output.begin(), x);
}

// -------------------------------------------------------------------------
int main()
{
   unsigned vertices;
   unsigned edges;

   scanf("%u", &vertices);
   edges = (vertices * (vertices - 1) / 2);

   std::vector<int> matrix(vertices * vertices);
   std::vector<std::vector<int>> incident(vertices);
   generateGraph(vertices, edges, matrix, incident);

   std::vector<bool> visited(vertices);
   std::vector<unsigned> output(vertices);

   for (unsigned i = 0; i < vertices; i++)
   {
      visited[i] = false;
      STEP = 0;
      output[i] = 0;
   }
   // ---------------- macierz sasiedztwa --------------------
   auto before = std::chrono::steady_clock::now();
   while (STEP < vertices)
   {
      for (unsigned i = 0; i < vertices; i++)
      {
         if (visited[i] == false)
            dfsMatrix(i, vertices, matrix, visited, output);

         if (STEP == vertices)
            break;
      }
   }
   auto after  = std::chrono::steady_clock::now();
   std::chrono::duration<double, std::milli> duration = after - before;
   printf("duration matrix: %f \n", duration.count());
   // ---------------- czyszczenie ---------------------------
   //
   for (unsigned i = 0; i < vertices; i++)
   {
      visited[i] = false;
      STEP = 0;
      output[i] = 0;
   }
   //
   // ---------------- lista incydencji ----------------------
   before = std::chrono::steady_clock::now();
   while (STEP < vertices)
   {
      for (unsigned i = 0; i < vertices; i++)
      {
         if (visited[i] == false)
            dfsList(i, vertices, incident, visited, output);

         if (STEP == vertices)
            break;
      }
   }
   after  = std::chrono::steady_clock::now();
   duration = after - before;
   printf("duration list:   %f \n", duration.count());
   return 0;
}
