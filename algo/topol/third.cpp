#include <cstdlib>
#include <cstdio>
#include <utility>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>
//
unsigned STEP = 0;
// -------------------------------------------------------- DFS ------------
void dfsMatrix(unsigned x, unsigned vertices, std::vector<int>& arr, 
               std::vector<bool>& visited, std::vector<unsigned>& output)
{
   for (unsigned i = 0; i < vertices; i++)
   {
      // przechodzenie w dol kolumny macierzy
      if (arr[i + x * vertices])
      {
         // sprawdzenie czy wierzcholek byl odwiedzany
         // i przechodzenie do nastepnego wierzcholka
         if (visited[i] == false)
         {
            visited[i] = true;
            dfsMatrix(i, vertices, arr, visited, output);
         }
      }
   }

   STEP++;
   // dopisywanie wierzcholka do poczatku listy wynikow
   output.insert(output.begin(), x);
}
// -------------------------------------------------------------------------
int main()
{
   unsigned vertices;
   unsigned edges;
   int      temp;

   FILE* pFile;
   pFile = fopen("topol.txt", "r");
   if (pFile == NULL)
      return -1;
   else 
   {
      fscanf(pFile, "%u", &vertices);

      // macierz sasiedztwa jako jednowymiarowa tablica (wektor)
      // pierwszy wierzcholek ma wartosc 0!
      std::vector<int> matrix(vertices * vertices);
      std::vector<bool> visited(vertices);

      std::vector<unsigned> output(vertices);

      while (!feof(pFile))
      {
         fscanf(pFile, "%d", &temp);
         matrix.push_back(temp);
      }
      fclose(pFile);
      edges = (vertices * (vertices - 1) / 2);

      // generowanie tablicy odwiedzonych wierzcholkow
      for (unsigned i = 0; i < vertices; i++)
         visited[i] = false;

      // macierz sasiedztwa
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
      // wypisywanie
      for (unsigned i = 0; i < vertices; i++)
         printf("%d ", output[i]);

      printf("\n");
   }
   return 0;
}
