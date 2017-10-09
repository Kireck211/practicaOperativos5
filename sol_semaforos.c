#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "sem.c"

#define CICLOS 10

void proceso(int);
void initsem(sem **, int);

char *pais[3]={"Peru","Bolvia","Colombia"};
sem *s;

int main()
{
	int pid;
	int status;
	int shmid;
	int args[3];
	int i;
	void *thread_result;


	initsem(&s,1);
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

void initsem(sem ** s, int n)
{
	int sem_id, count_id, queue_id;
	int errnum;

	//Inicialización de memoria para struct sem
	sem_id= shmget(0x1234, sizeof(sem), 0666|IPC_CREAT);		//Obtiene el ID de la memoria
	if(sem_id == -1)
	{
		errnum = errno;
		fprintf(stderr, "Value of errno: %d\n", errno);
		perror("Error printed by perror");
		printf("Error en shmget\n");
		exit(1);
	}
	*s = (sem*)shmat(sem_id, NULL, 0);						//Obtiene el apuntador de la memoria
	if(*s == NULL)
	{
		printf("Error en shmat\n");
		exit(2);
	}

	//Inicialización de memoria para sem.queue
	queue_id = shmget(0x1236, sizeof(queue), 0666|IPC_CREAT);
	if(queue_id == -1)
	{
		printf("Error en shmget\n");
		exit(1);
	}
	(*s)->blocked = (queue*)shmat(queue_id, NULL, 0);
	if((*s)->blocked == NULL)
	{
		printf("Error en shmat\n");
		exit(2);
	}

	(*s)->count = n;
	initqueue((*s)->blocked);
}