#include <iostream>

int NWD(int a, int b)
{
   while (a != b)
      if (a > b)
         a -=b;
      else
         b -= a;
   return a;
}

int main(int argc, char** argv)
{
   std::cout << std::endl << argv[0] << std::endl;
   int a, b;

   while (true)
   {
      try 
      {
         std::cin >> a >> b;
         if (a < 0 || b < 0 || std::cin.fail())
            throw 1;

         std::cout << NWD(a, b) << std::endl;
      }
      catch(...)
      {
         std::cout << "Podales bledne dane" << std::endl;
         std::cin.clear();

         break;
      }
   }
   return 0;
}
