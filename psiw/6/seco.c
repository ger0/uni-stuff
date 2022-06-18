#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
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

int main(){
    int shmid;
    int *buf;
    int semid = semget(145227, 2, 0600);
    if (semid == -1){
      perror("Uzyskanie identyfikatora tablicy semaforow");
      exit(1);
    }

    shmid = shmget(145227, sizeof(int), IPC_CREAT|0600);
    if (shmid == -1){
	perror("Utworzenie segmentu pamieci wspoldzielonej");
	exit(1);
    }
    buf = (int*)shmat(shmid, NULL, 0);
    if (buf == NULL){
	perror("Przylaczenie segmentu pamieci wspoldzielonej");
	exit(1);
    }
    for (unsigned i = 0; i < 100; i++){
	opusc(semid, 1);
	printf("Wartosc: %d\n", *buf);
	podnies(semid, 0);
    }
    return 0;
}
