#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "sem.c"


#define CICLOS 10

char *pais[3]={"Peru","Bolvia","Colombia"};

sem *s;

void proceso(int i)
{
	int k;
	int l;

	for(k=0;k<CICLOS;k++)
	{
		
		waitsem(s);		
		printf("Entra %s",pais[i]);
		fflush(stdout);
		sleep(rand()%3);
		printf("- %s Sale\n",pais[i]);

		signalsem(s);

		// Espera aleatoria fuera de la sección crítica
		sleep(rand()%3);
	}
	exit(0); // Termina el proceso
}

int main()
{
	int pid;
	int status;
	int shmid;
	int args[3];
	int i;
	void *thread_result;


	initsem(s, 1);
	srand(getpid());

	for(i=0;i<3;i++)
	{
		// Crea un nuevo proceso hijo que ejecuta la función proceso()
		pid=fork();
		if(pid==0)
			proceso(i);
	}

	for(i=0;i<3;i++)
		pid = wait(&status);
	
	// Eliminar la memoria compartida
	shmdt(s);
}