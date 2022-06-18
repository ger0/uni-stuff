#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

static struct sembuf buf;

void podnies(int semid, int semnum){
   buf.sem_num = semnum;
   buf.sem_op = 1;
   buf.sem_flg = 0;
   if (semop(semid, &buf, 1) == -1){
      perror("Podnoszenie semafora");
      exit(1);
   }
}

void opusc(int semid, int semnum){
   buf.sem_num = semnum;
   buf.sem_op = -1;
   buf.sem_flg = 0;
   if (semop(semid, &buf, 1) == -1){
      perror("Opuszczenie semafora");
      exit(1);
   }
}
#define MAX 10

int main(){
   int shmid, semid, i;
   int *buf;
   
   semid = semget(45281, 2, 0600);
   if (semid == -1){
      perror("Uzyskanie identyfikatora tablicy semaforow");
      exit(1);
   }

   shmid = shmget(45281, MAX*sizeof(int), 0600);
   if (shmid == -1){
      perror("Uzyskanie identyfikatora segmentu pamieci wspoldzielonej");
      exit(1);
   }
   
   buf = (int*)shmat(shmid, NULL, 0);
   if (buf == NULL){
      perror("Przylaczenie segmentu pamieci wspoldzielonej");
      exit(1);
   }

   for (i=0; i<10000; i++){
      opusc(semid, 1);
      sleep(1);
      printf("Numer: %5d   Wartosc: %5d\n", i, buf[i%MAX]);
      podnies(semid, 0);
   }
}
