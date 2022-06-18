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
    int semid = semget(145227, 2, IPC_CREAT|0600);
    if (semid == -1) {
      perror("Utworzenie tablicy semaforow");
      exit(1);
    }
    if (semctl(semid, 0, SETVAL, (int)1) == -1) {
	perror("Nadanie sem wart 0");
	exit(1);
    }
    if (semctl(semid, 1, SETVAL, (int)0) == -1) {
	perror("Nadanie sem wart 1");
	exit(1);
    }
    int shmid = shmget(145227, sizeof(int), IPC_CREAT|0600);
    if (shmid == -1){
	perror("tworzenie pamieci");
	exit(1);
    }
    int *buf;
    buf = (int*)shmat(shmid, NULL, 0);
    if (buf == NULL){
	perror("przylaczanie pamieci");
	exit(1);
    }
    for (int i = 1; i <= 100; i++){
	opusc(semid, 0);
	*buf = i;
	podnies(semid, 1);
	printf("Zapis: %i\n", *buf);
    }
    return 0;
}
