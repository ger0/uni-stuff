#include <cstdlib>
#include <ctime>
#include <chrono>
#include <utility>
#include <iostream>

using namespace std;
//    ---------------- struktura listy -----------
struct List
{
   int number;
   List* next;
};
//    ---------------- badanie rozmiaru ----------
unsigned listSize(List* list)
{
	int dlugosc = 1;
	if (list->next != NULL)
   {
		dlugosc++;
		List *pointer = list->next;
		while(pointer->next != NULL)
      {
			pointer = pointer->next;
			dlugosc++;
		}
	}
	return dlugosc;
}
//    ---------------- dodwanie elementu ---------
void push(List* list, int number)
{
	if (list->next == NULL)
		list->next = (struct List*)malloc(sizeof(struct List));
	else
   {
		List *pointer = list->next;
		while (pointer->next != NULL)
			pointer = pointer->next;

		pointer->next = (struct List*)malloc(sizeof(struct List));
	}
} 

//    ---------------- usuwanie elementu ---------
struct List* deleteFirst(List* list)
{
   List* ptr = NULL;
   if (list != NULL)
   {
      List* ptr = list->next;
      free(list);
   }
   return ptr; 
}
//    --------------- insert --------------------  
void insert(List* list, int number, int position)
{
	List *pointer;
	if (position == 0)
   {
		pointer = (struct List*)malloc(sizeof(struct List));
      pointer->number = number;
      pointer->next   = list->next; 
		list->number = number;
		list->next = pointer;
	}
   else if (position == 1)
   {
		pointer = list->next;
      list->next = (struct List*)malloc(sizeof(struct List));
      list->next->number = number;
      list->next->next   = pointer;
	}
   else
   {
		pointer = list->next;
		for (int i = 2; i < position; i++)
      {
			pointer = pointer->next;
		}
      List* temp = (struct List*)malloc(sizeof(struct List));
      temp->number = number;
      temp->next   = pointer->next;
      pointer->next = temp;
	}
}
// ---------------------- create -
void createSorted(List* list, int array[], int size)
{
   if (list == NULL)
   {
      struct List* temp = (struct List*)malloc(sizeof(struct List));
      list = temp;
      list->next = NULL;
   }
	list->number = array[0];
	List *pointer = list;
	List *firstPointer = list;
	for (int i = 1; i < size; i++)
   {
		pointer = firstPointer;
		for (int j = 0; j < i; j++)
      {
			if (array[i] >= pointer->number)
         {
				if (pointer->next == NULL)
            {
               pointer->next = (struct List*)malloc(sizeof(struct List*));
               pointer->next->number = array[i];
               pointer->next->next   = NULL;
					break;
				}
				else
					pointer = pointer->next;
			}
         else
         {
            List* temp = (struct List*)malloc(sizeof(struct List*));
            temp->number = pointer->number;
            temp->next   = pointer->next;
            pointer->next = temp;
				pointer->number = array[i];
				break;
			}
		}
	}
}
//---------------------------- wyszukiwanie --------------
int search(List* list, int target, unsigned size)
{
   List* pointer = list;
   int i = 1;
   while (pointer != NULL)
   {
      if (pointer->number == target)
         return i;
      else
      {
         pointer = pointer->next;
         i++;
      }
   }
   return -1;
}
int main()
{
   // ustalanie krokow 
   unsigned start = 1000;
	unsigned step  = 0;

   unsigned size;
   unsigned steps = 1;
   // koniec ustalania krokow

	double tworzenie[steps];
	double szukanie[steps];
   double usuwanie[steps];
   for(int s = 0; s < steps; s++)
   {
      size = start + step * s;
      int arr[size];
      for (int i = 0; i < size; i++)
         arr[i] = i;

      srand(time(NULL));
      for (int i = 0; i < size; i++)
         std::swap(arr[i], arr[rand() % size]);

		auto begin = chrono::steady_clock::now();
      auto end   = chrono::steady_clock::now();
      chrono::duration<double, std::milli> elapsed = end - begin;

      struct List* list = NULL;
      
      begin = chrono::steady_clock::now();
      createSorted(list, arr, size);
      end   = chrono::steady_clock::now();
      elapsed = end - begin;
      cout << "Tworzenie:" << endl;
		cout << elapsed.count() << endl;
		tworzenie[s] = elapsed.count();
      // WYSZUKIWANIE
		begin = chrono::steady_clock::now();
		for(int i = 0; i < size; i++)
			search(list, arr[i], size);
		end = chrono::steady_clock::now();
      elapsed = end - begin;
      cout << "Szukanie:" << endl;
		cout << elapsed.count() << endl;
		szukanie[s] = elapsed.count();
      
      // USUWANIE
      begin = chrono::steady_clock::now();
		for(int i = 0; i < size; i++)
			list = deleteFirst(list);
      end   = chrono::steady_clock::now();
      elapsed = end - begin;
      cout << "Usuwanie:" << endl;
		cout << elapsed.count() << endl;
		usuwanie[s] = elapsed.count();

	}
/*	for(int j = 0; j < steps; j++)
		cout << tworzenie[j] << ";"; 
	cout << endl;
	
	for(int j = 0; j < steps; j++)
		cout << szukanie[j] << ";"; 
	cout << endl;
	
	for(int j = 0; j < steps; j++)
		cout << usuwanie[j] << ";"; 
	cout << endl;	
   */
	
	
	return 0;
}
