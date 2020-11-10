#include <cstdlib>
#include <cstdio>
#include <utility>
#include <ctime>
#include <vector>
#include <algorithm>

const unsigned PERCENT = 60;
unsigned       STEP    = 0;

// ------------------------------------- tasowanie -------------------------
void shuffle(int* arr, unsigned size)
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
         if (temp[i])
            incarr[x].push_back(y);
         i++;
      }
   }
}
// -------------------------------------------------------- DFS ------------
void dfsMatrix(unsigned vertices, std::vector<int>& arr, 
               std::vector<unsigned>& visited, std::vector<unsigned>& output)
{
   unsigned x = visited.back();
   std::vector<unsigned> stack;
   for (unsigned y = 0; y < vertices; y++)
   {
      bool exist = false;

      if (arr[x + y * vertices])
      {
         for (unsigned i = 0; i < visited.size(); i++)
         {
            if (y ==  visited[i])
            {
               exist = true;
               break;
            }
         }

         if (!exist)
            stack.push_back(y);
      }
   }
   
   // wybieranie od mniejszego klucza
   std::sort(stack.begin(), stack.end());

   for (unsigned i = 0; i < stack.size(); i++)
   {
      bool exist = false;

      for (unsigned j = 0; j < visited.size(); j++)
      {
         if (stack[i] == visited[j])
         {
            exist = true;
            break;
         }
      }

      if (!exist)
      {
         visited.push_back(stack[i]);
         dfsMatrix(vertices, arr, visited, output);
      }
   }

   STEP++;
   output.insert(output.begin(), x);
   // ------------------------------------
//   printf("%u ", x);
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

   std::vector<unsigned> visited;
   std::vector<unsigned> output;

   visited.push_back(0);
   dfsMatrix(vertices, matrix, visited, output);

   while (STEP < vertices)
   {
      break;
   }

   /*
   for (unsigned i = 0; i < output.size(); i++)
      printf("%u ", output[i]);
      */

   printf("\n");
   // wypis - - - - - - - - - - - - - - - - -
   /*
   for (unsigned y = 0; y < vertices; y++)
   {
      for (unsigned x = 0; x < vertices; x++)
         printf("%d ", matrix[x + y * vertices]);
      printf("\n");
   }

   for (unsigned i = 0; i < vertices; i++)
   {
      printf("%d: ", i);
      for (unsigned j = 0; j < incident[i].size(); j++)
         printf("%d ", incident[i][j]);
      printf("\n");
   }
   */
   return 0;
}
