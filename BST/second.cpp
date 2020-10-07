#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <chrono>
#include <vector>
#include <utility>

unsigned SIZE = 1000;
unsigned maxHeight = 0;
//---------------------------------------------------- struktura drzewa
struct tree
{
	int info;
	struct tree *left;
	struct tree *right;
};
//--------------------------------------------------- budowa drzewa BST
struct tree *newTree(int x)
{
   struct tree* temp = (struct tree *)malloc(sizeof(struct tree));
   temp->info = x;
   temp->left = NULL;
   temp->right = NULL;
   return(temp);
}

struct tree *insert(struct tree *root, int x)
{
	if (root == NULL)     // jezeli drzewo jest puste
      return newTree(x);
   if (root->info > x)
	   root->left = insert(root->left, x);
   else if (root->info < x)
      root->right = insert(root->right, x);

	return(root);
}
// usuwanie drzewa BST (zwalnianie alokacji pamieci)
void postorderRemoval(struct tree *root) // powinno usuwac 
{
	if (root != NULL)
   {
		postorderRemoval(root->left);
		postorderRemoval(root->right);
      free(root);
	}
}
// ------------------------------------------------  wypisywanie drzew
void inOrder(struct tree *root)
{
	if(root != NULL)
   {
		inOrder(root->left);
		printf(" %d", root->info);
		inOrder(root->right);
	}
}
//----------------------------------- budowanie zrownowazonego drzewa
void inOrderARR(struct tree *root, std::vector<tree*> &arr)
{
	if(root != NULL)
   {
		inOrderARR(root->left, arr);
      arr.push_back(root);
		//printf(" %d", root->info);
		inOrderARR(root->right, arr);
	}
}

struct tree* buildBAL(std::vector<tree*> &trees, int start, int end)
{
   if (start > end)
      return NULL;

   int mid = (start + end) / 2;
   struct tree* root = trees[mid];
   root->left = buildBAL(trees, start, mid - 1);
   root->right = buildBAL(trees, mid + 1, end);

   return root;
}

struct tree* buildBALTree(tree* root)
{
   std::vector<tree*> trees;
   inOrderARR(root, trees);

   return buildBAL(trees, 0, (int)SIZE - 1);
}
//------------------------------------------------------------------

//obliczanie wysokosci
void preorderH(struct tree *root, int height)
{
	if(root != NULL)
   {
		preorderH(root->left, height + 1);
		preorderH(root->right, height + 1);
	}
   else if (height > maxHeight)
      maxHeight = height;
}
// --------------------- tasowanie elementow uporzadkowanej tablicy
void shuffle(int *arr)
{
   if (SIZE > 1)
   {
      srand(time(NULL));
      for (unsigned i = 0; i < SIZE - 1; i++)
      {
         unsigned j = i + rand() / (RAND_MAX / (SIZE - i) + 1);
         int t = arr[j];
         arr[j] = arr[i];
         arr[i] = t;
      }
   }
}
// ---------------------------------------------------------------
int main(int argc, char** argv)
{
   if (argc ==2)
      SIZE = strtoul(argv[1], NULL, 10);
   srand(time(NULL));

   unsigned pocz, krok, ilosc;
   scanf("%d", &pocz);
   scanf("%d", &krok);
   scanf("%d", &ilosc);
   printf("%d, %d, %d ", pocz, krok, ilosc);
   
   for (unsigned i = pocz; i < pocz + krok * ilosc; i = i + krok)
   {
      SIZE = i;
      printf("\n%u; ", SIZE);
      // generowanie "losowej" tablicy bez powtorzen
      int arr[SIZE];
      for (int i = 0; i < SIZE; i++)
         arr[i] = i;
      shuffle(arr);

      // tworzenie BST
      struct tree *root = NULL;
      for (unsigned i = 0; i < SIZE; i++)
         root = insert(root, arr[i]);
      
      // pomiar wysokosci BST
      maxHeight = 0;
      preorderH(root, 0);
      printf("%d; ", maxHeight - 1);

      
      // rownowazenie drzewa BST (tworzenie nowego)
      struct tree* balancedBST = NULL;
      balancedBST = buildBALTree(root);
   // pomiar wysokosci zrownowazonego drzewa 
      maxHeight = 0;
      preorderH(balancedBST, 0);
      printf("%d", maxHeight - 1); 
      
      // usuwanie dynamicznie zaalokowanej pamieci
      postorderRemoval(root);
   }

   return 0;
}
