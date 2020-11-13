#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    close(1);
    close(2);

    int id = creat("log.txt", 0600);

    dup2(id, STDERR_FILENO);

    int pidArr[argc];
    for(int i = 1; i < argc; i++)
    {
	if ((pidArr[i] = fork()) == 0)
	{
	    execlp(argv[i], argv[i], NULL);
	    perror(argv[i]);
	    exit(0);
	}
    }

    while (1)
    {
	int state;
	int pid = wait(&state);
	for (int i = 1; i < argc; i++)
	{
	    if (pid == pidArr[i])
	    {
		if ((pidArr[i] = fork()) == 0)
		{
			execlp(argv[i], argv[i], NULL);
			perror(argv[i]);
			exit(0);
		}
	    }
	}
	sleep(1);
    }
    exit(0);
    return 0;
}
