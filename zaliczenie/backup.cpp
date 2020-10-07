#include <cstdlib>
#include <cstdio>
#include <utility>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>

std::vector<unsigned> V;
std::vector<unsigned> C;
unsigned zrodlo = 0;
unsigned counter = 1;

// ------------------------------------- EULER -----------------------------
void eulerM(unsigned& v, unsigned& vertices, std::vector<unsigned> &arr)
{
   for (unsigned w = 0; w < vertices; w++)
   {
      if (arr[w + v * vertices])
      {
         arr[w + v * vertices] -= 1;

         if (arr[v + w * vertices] == 0)
            printf("ERROR\n");

         arr[v + w * vertices] -= 1;

         eulerM(w, vertices, arr);
      }
   }
   C.push_back(v);
}

// ------------------------------------- HAMILTON --------------------------
void hamiltonM(unsigned& v, unsigned& vertices, std::vector<unsigned> &arr, std::vector<bool> &visited)
{
   if (V.size() == vertices)
   {
      if (arr[zrodlo + v * vertices])
      {
         printf("%u: ", counter);
         for (unsigned i = 0; i < vertices; i++)
         {
            printf("%u ", V[i] + 1);
         }
         counter++;
         printf("\n");
      }
      return;
   }

   unsigned w = 0;

   while (w < vertices)
   {
      if (arr[w + v * vertices])
      {
         if (!visited[w])
         {
            visited[w] = true;
            V.push_back(w);

            hamiltonM(w, vertices, arr, visited);

            // cofnij
            visited[w] = false;
            V.pop_back();
         }
      }
      w++;
   }
}
// -------------------------------------------------------------------------
int main()
{
   srand(time(NULL));

   unsigned vertices = 6;

   std::vector<unsigned> mat(vertices * vertices);
   std::vector<bool>     visited(vertices);

   FILE* pFile;
   pFile = fopen("test.txt", "r");
   if (pFile == NULL)
      return -1;
   else 
   {
      unsigned temp = 0;
      for (unsigned i = 0; i < vertices * vertices; i++)
      {
         fscanf(pFile, "%u", &temp);
         mat[i] = temp;
      }
      fclose(pFile);
   }
   for (unsigned i = 0; i < visited.size(); i++)
      visited[i] = false;

   unsigned v = 0;
   zrodlo = v;

   // /*
   visited[zrodlo] = true;
   V.push_back(zrodlo);
   hamiltonM(v, vertices, mat, visited);
   // */

   printf("\n");

   eulerM(v, vertices, mat);
   for (unsigned i = 0; i < C.size(); i++)
      printf("%u ", C[i] + 1);

   printf("\n");
   return 0;
}

