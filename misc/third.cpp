#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <chrono>
#include <vector>
#include <utility>

unsigned SIZE = 1000;
unsigned maxHeight = 0;

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
// --------------------------------------------- wyszukiwanie w drzewie
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
// ------------------------------------------  wypisywanie drzew inorder
void inOrder(struct tree *root)
{
	if(root != NULL)
   {
		inOrder(root->left);
		printf(" %d", root->info);
		inOrder(root->right);
	}
}
// --------------------------- usuwanie postorder dla BST
void postorderRemoval(struct tree *root)
{
	if (root != NULL)
   {
		postorderRemoval(root->left);
		postorderRemoval(root->right);
		printf("%d ", root->info);
      free(root);
	}
	return;
}

//-----------------------------------------------obliczanie wysokosci
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

int main(int argc, char** argv)
{
   if (argc ==2)
      SIZE = strtoul(argv[1], NULL, 10);

   std::vector<int> arr;
   int temp = 0;

   FILE* pFile;

   pFile = fopen("file.txt", "r");
   if (pFile == NULL)
      return -1;
   else
   {
      while (!feof(pFile))
      {
         fscanf(pFile, "%d", &temp);
         arr.push_back(temp);
      }
      fclose(pFile);
   }

   arr.pop_back();
   SIZE = arr.size();

   // tworzenie BST
   struct tree *root = NULL;
   for (unsigned i = 0; i < SIZE; i++)
      root = insert(root, arr[i]);

   // pomiar wysokosci BST
   maxHeight = 0;
   preorderH(root, 0);
   printf("wysokosc: %d\n", maxHeight - 1);
   
   // usuwanie BST
   postorderRemoval(root);

   return 0;
}
