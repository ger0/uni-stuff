#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
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
    for (unsigned i = 1; i <= 100; i++){
	while (buf[1] != 0){}

	buf[1] = 1;
	buf[0] = i;
	printf("Zapis: %i\n", buf[0]);
	sleep(1);
    }
    return 0;
}
