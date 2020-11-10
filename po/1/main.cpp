#include <cstdio>
#include <string>
#include <vector>
#include <ctime>

class Czlowiek
{
protected:
   std::string imie, nazwisko;
   Czlowiek(std::string m_imie, std::string m_nazw):
      imie(m_imie), nazwisko(m_nazw) {}
   virtual ~Czlowiek() {};
public:
   virtual void pij() = 0;
   virtual void przedstawSie()
   {
      printf("Imie: %s, Nazwisko: %s\n", imie.c_str(), nazwisko.c_str());
   }
};

class Pracownik: public Czlowiek
{
public:
   Pracownik(std::string imie, std::string nazwisko) : 
      Czlowiek(imie, nazwisko) {}
   void pij()
   {
      printf("Pije na smutno\n");
   }
};

class Student: public Czlowiek
{
private:
   int nrId;
public:
   Student(std::string imie, std::string nazwisko, int id) : 
      Czlowiek(imie, nazwisko), nrId(id) {}
   void pij()
   {
      printf("Pije na wesolo\n");
   }

   virtual void przedstawSie()
   {
      printf("Imie: %s, Nazwisko: %s, Nr Indeksu: %u\n", 
            imie.c_str(), nazwisko.c_str(), nrId);
   }
};

int main()
{
   unsigned n = 0;

   std::vector<Pracownik> pracownicy;
   pracownicy.push_back(Pracownik("Andrzej",    "Andrzejewski"));
   pracownicy.push_back(Pracownik("Krzysztof",  "Dziwny"));
   pracownicy.push_back(Pracownik("Dariusz",    "Brzezinski"));

   std::vector<Student> studenci;
   studenci.push_back(Student("Maciej",   "Grzes",   145227));
   studenci.push_back(Student("Dziwny",   "Typ",     112112)); 
   studenci.push_back(Student("Andrzej",  "Kapsoski",666666));

   printf("Podaj liczbe osob w kolejce\n");
   scanf("%u", &n);
   std::vector<Czlowiek*> queue(n);

   srand(time(NULL));

   for (unsigned i = 0; i < n; i++)
   {
      if (rand() % 2)
         queue.push_back(&pracownicy[rand() % pracownicy.size()]);
      else
         queue.push_back(&studenci[rand() % studenci.size()]);
   }

   for (unsigned i = 0; i < n; i++)
   {
      queue.back()->przedstawSie();
      queue.back()->pij();
      printf("\n");
      queue.pop_back();
   }

   return 0;
}
