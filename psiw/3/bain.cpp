#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
   close(1);
   creat("ls.txt", 0600);
   execvp("ls", argv);
}
