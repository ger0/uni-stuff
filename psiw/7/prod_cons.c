#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 5

int buf[MAX];
int num = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t c2 = PTHREAD_COND_INITIALIZER;

void* prod(void *p) {
   int index = 0;
   int i;
   for (i=0;i<100;i++){
      buf[index] = i;
      num++;
      index = (index + 1) % MAX;
   }
}

void* kons(void *p) {
   int index = 0;
   int i;
   for (i=0;i<100;i++){
      printf("%d\n", buf[index]);
      num--;
      index = (index + 1) % MAX;
   }
}

int main() {
   pthread_t pth1, pth2;
   pthread_create(&pth1, NULL, prod, NULL);
   pthread_create(&pth2, NULL, kons, NULL);
   pthread_join(pth1, NULL);
   pthread_join(pth2, NULL);
}
