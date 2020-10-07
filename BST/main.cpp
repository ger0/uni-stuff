#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <chrono>
#include <vector>
#include <utility>

unsigned SIZE = 1000;
std::vector<int> post;

struct tree
{
	int info;
	struct tree *left;
	struct tree *right;
};

//--------------------------------------------------budowa drzewa
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
//-------------------------------mo?e si? przydac do szukania ale trzeba przerobi?
struct tree *search(struct tree *root, int x) 
{
	struct tree *ptr;
	ptr = root;
	while (ptr)
   {
		if (x > ptr->info)
		     ptr = ptr->right; 
      else if (x < ptr->info)
		     ptr = ptr->left; 
      else
		     break;
	}
   return ptr;
}
void postorderRemoval(struct tree *root) // powinno usuwac 
{
	if (root != NULL)
   {
		postorderRemoval(root->left);
		postorderRemoval(root->right);
      post.push_back(root);
      free(root);
	}
	return;
}
// ----------------------- tasuje elementy uporzadkowanej tablicy -----------
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

int main(int argc, char** argv)
{
   if (argc ==2)
      SIZE = strtoul(argv[1], NULL, 10);
   srand(time(NULL));
   
   // generowanie "losowej" tablicy bez powtorzen
   int arr[SIZE];
   for (int i = 0; i < SIZE; i++)
      arr[i] = i;
   shuffle(arr);


   struct tree *root = NULL;

   // tworzenie BST
   auto before = std::chrono::steady_clock::now();
   for (unsigned i = 0; i < SIZE; i++)
   {
      root = insert(root, arr[i]);
   }
   auto after = std::chrono::steady_clock::now();
   std::chrono::duration<double, std::milli> duration = after - before;
   printf("%f;", duration.count());

   // przeszukiwanie BST
   before = std::chrono::steady_clock::now();
   for (unsigned i = 0; i < SIZE; i++)
   {
      search(root, arr[i]);
   }
   after = std::chrono::steady_clock::now();
   duration = after - before;
   printf("%f;", duration.count());

   // usuwanie BST
   before = std::chrono::steady_clock::now();
   postorderRemoval(root);
   after  = std::chrono::steady_clock::now();
   duration = after - before;
   printf("%f\n", duration.count());

   return 0;
}
