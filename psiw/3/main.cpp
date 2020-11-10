#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void f(int sig_num)
{
   printf("Przechwycenie syg nr. %d\n", sig_num);
}
int main(int argc, char* argv[])
{
   printf("def\n");
   signal(SIGINT, SIG_DFL);
   sleep(5);
   printf("IGNORE\n");
   sleep(5);
   printf("Przechwyt\n");
   signal(SIGINT, f);
   sleep(5);
}
