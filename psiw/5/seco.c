#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
    int shmid;
    int *buf;

    shmid = shmget(145227, 2 * sizeof(int), IPC_CREAT|0600);
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
	while (buf[1] != 1) {}

	sleep(1);
	printf("Wartosc: %d\n", buf[0]);
	buf[1] = 0;
    }
    return 0;
}
