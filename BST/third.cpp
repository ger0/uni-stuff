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
//----------------------------------- budowanie zrownowazonego drzewa
void inOrderARR(struct tree *root, std::vector<tree*> &arr)
{
	if (root != NULL)
   {
		inOrderARR(root->left, arr);
      arr.push_back(root);
		inOrderARR(root->right, arr);
	}
}
struct tree* buildBAL(std::vector<tree*> &trees, int start, int end)
{
   if (start > end)
   {
      return NULL;
   }

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
// wyszukiwanie elementu od wysokosci
void preOrderS(struct tree *root, int height, int elem)
{
	if(root != NULL)
   {
      if (elem == root->info)
         printf("Element %d, na wys: %d\n", elem, height);
		preOrderS(root->left, height + 1, elem);
		preOrderS(root->right, height + 1, elem);
	}
}
//-----------------------------------------------obliczanie wysokosci
void preorderH(struct tree *root, int height)
{
	if(root != NULL)
   {
      printf("%d ", root->info);
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

//   for (unsigned i = 0; i < SIZE; i++)
//      printf("%d, ", arr[i]);


   /*     OBLICZANIE CZASU
   auto before = std::chrono::steady_clock::now();
   auto after = std::chrono::steady_clock::now();
   std::chrono::duration<double, std::milli> duration = after - before;
   */

   // tworzenie BST
   struct tree *root = NULL;
   for (unsigned i = 0; i < SIZE; i++)
      root = insert(root, arr[i]);

   preOrderS(root, 0, 1);
   
   // pomiar wysokosci BST
   maxHeight = 0;
   printf("pre order: ");
   preorderH(root, 0);
   printf("\n");

   printf("wys BST %d\n", maxHeight - 1);

   printf("in order: ");
   inOrder(root);
   printf("\n");

   printf("post order: ");
   // usuwanie BST
   postorderRemoval(root);
   printf("\n");
   // przeszukiwanie BST
   /*
   for (unsigned i = 0; i < SIZE; i++)
      search(root, arr[i]);
   
      */
   
   /*
   // rownowazenie drzewa BST (tworzenie nowego)
   struct tree* balancedBST = NULL;
   balancedBST = buildBALTree(root);

   // pomiar wysokosci zrownowazonego drzewa 
   maxHeight = 0;
   preorderH(balancedBST, 0);
   printf("wys AVL%d", maxHeight - 1); 
   printf("\n");
   */



   return 0;
}
