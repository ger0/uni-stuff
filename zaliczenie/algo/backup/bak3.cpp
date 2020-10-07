#include <cstdlib>
#include <cstdio>
#include <utility>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>

const float    DENSITY = 0.7;

std::vector<unsigned> C;
std::vector<unsigned> V;

bool done = false;
unsigned zrodlo = 0;

// ------------------------------------- HAMILTON --------------------------
void hamiltonM(unsigned& v, unsigned& vertices, std::vector<unsigned> &arr)
{
   if (done)
      return;

   V.push_back(v);
   unsigned w = 0;

   while (w < vertices && !(done))
   {
      if (arr[w + v * vertices])
      {
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
            hamiltonM(w, vertices, arr);

         if (done)
            return;
      }
      w++;
   }
   if (V.size() == vertices && (arr[v + zrodlo * vertices] && arr[zrodlo + v * vertices]))
   {
      done = true;
   }

   else
      V.pop_back();

}
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
// MACIERZ WERSJA!!!
void generateGraphM(unsigned vertices, unsigned edges, std::vector<unsigned> &arr)
{
   // przypisuje do kazdej krawedzi nastepny wierzcholek 
   for (unsigned i = 0; i < vertices; i++)
   {
      arr[((i + 1) % vertices) + vertices * i] += 1;
      arr[((i) % vertices) + vertices * ((i + 1) % vertices)] += 1;
   }
   // tasowanie wierzcholkow
   std::vector<unsigned> shuffler(vertices);
   for (unsigned i = 0; i < vertices; i++)
      shuffler[i] = i;
   shuffle(shuffler, vertices);

   for (unsigned i = 0; i < vertices; i++)
   {
      unsigned idx = shuffler[i];
      for (unsigned j = 0; j < vertices; j++)
         std::swap(arr[j + i * vertices], arr[j + idx * vertices]);

      for (unsigned j = 0; j < vertices; j++)
         std::swap(arr[i + j * vertices], arr[idx + j * vertices]);
   }

   // pozostale krawedzie do dopisania
   unsigned vertLeft = 0;
   vertLeft = edges - vertices;

   if (int(edges - vertices) < 0)
      vertLeft = 0;

   unsigned a, b, c;

   for (unsigned i = 0; i < vertLeft; i += 3)
   {
      a = rand() % vertices;
      b = rand() % vertices;
      if (b == a)
      {
         b += 1;
         b = b % vertices;
      }
      c = rand() % vertices;
      if (c == b)
         c += 1;
      else if (c == a) 
         c += 2;
      c = c % vertices;

      arr[b + vertices * a] += 1;
      arr[a + vertices * b] += 1;

      arr[c + vertices * a] += 1;
      arr[a + vertices * c] += 1;

      arr[c + vertices * b] += 1;
      arr[b + vertices * c] += 1;
   }
   /*
   for (unsigned y = 0; y < vertices; y++)
   {
      for (unsigned x = 0; x < vertices; x++)
      {
         printf("%d ", arr[x + y * vertices]);
      }
      printf("\n");
   }
   */
}
// -------------------------------------------------------------------------
int main()
{
   srand(time(NULL));

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

      std::vector<unsigned> mat(vertices * vertices);
      std::vector<unsigned> mat2(vertices * vertices);

      for (unsigned i = 0; i < mat.size(); i++)
         mat[i] = 0;

      edges = DENSITY * (vertices * (vertices - 1) / 2);
      generateGraphM(vertices, edges, mat);
      std::copy(mat.begin(), mat.end(), mat2.begin());

      unsigned v = 0;

      before = std::chrono::steady_clock::now();
      eulerM(v, vertices, mat);
      after = std::chrono::steady_clock::now();
      duration = after - before;

      printf("%u;%f;",vertices, duration.count());
      
      zrodlo = v;
      before = std::chrono::steady_clock::now();
      hamiltonM(v, vertices, mat2);
      after = std::chrono::steady_clock::now();
      duration = after - before;

      printf("%f", duration.count());
      printf("\n");
      // czyszczenie wektorow
      done = false;
      V.clear();
      C.clear();
   }
   return 0;
}

