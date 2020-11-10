#include <vector>
#include <cstdio>
#include <string>

class Gitara 
{
private:
   std::string name;
public:
   Gitara(std::string m_nam):
      name(m_nam) {}
   void print()
   {
      printf("%s", name.c_str());
   }
};

class Magazyn
{
private:
   std::vector<Gitara*> content;
public:
   Magazyn& operator+=(Gitara* gitara)
   {
      content.push_back(gitara);
      return *this;
   }
   void print()
   {
      for (unsigned i = 0; i < content.size(); i++)
      {
         content[i]->print();
         printf(", ");
      }
      printf("\n");
   }
   Magazyn& operator-=(Gitara* gitara)
   {
      for (auto it = content.begin(); it != content.end(); )
      {
         if (*it == gitara)
            it = content.erase(it);
         else
            ++it;
      }
      return *this;
   }
};

int main()
{
   Gitara gitara(std::string("dong"));
   Gitara gitar(std::string("bong"));
   Magazyn magazyn;
   magazyn+= &gitara;
   magazyn+= &gitar;

   magazyn.print();
   magazyn-= &gitar;
   magazyn.print();
   return 0;
}
