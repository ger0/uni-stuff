#include <stdio.h>
#include <unistd.h>

int main(){
   int d;
   char buf[10];

   mkfifo("kolejka.fifo", 0600);

   if ( fork() == 0 ) {
    printf("A");
      d = open("kolejka.fifo", O_RDONLY);
      printf("B");
      read(d, buf, 3); 
      printf("C");
	    read(d, buf, 1); 
	    D;
   }
   else {
      printf("D");
      d = open("kolejka.fifo", O_WRONLY);
      printf("E");
      write(d, buf, 2); 
      printf("F");
   }
   pause(); // czekaj w niesko?czono??
}
