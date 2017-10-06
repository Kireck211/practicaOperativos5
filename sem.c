#include <stdio.h>
#include "sem.h"


void initsem(sem *s, int i)
{
	int sem_id, count_id, queue_id;

	//Inicialización de memoria para struct sem
	sem_id= shmget(0x1234, sizeof(s), 0666|IPC_CREAT);		//Obtiene el ID de la memoria
	if(sem_id == -1)
	{
		printf("Error en shmget\n");
		exit(1);
	}
	s = (sem*)shmat(sem_id, NULL, 0);						//Obtiene el apuntador de la memoria
	if(s == NULL)
	{
		printf("Error en shmat\n");
		exit(2);
	}

	//Inicialización de memoria para sem.count
	count_id = shmget(0x1235, sizeof(int), 0666|IPC_CREAT);
	if(count_id == -1)
	{
		printf("Error en shmget\n");
		exit(1);
	}
	s->count = shmat(count_id, NULL, 0);
	if(s->count == NULL)
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
	s->blocked = shmat(count_id, NULL, 0);
	if(s->blocked == NULL)
	{
		printf("Error en shmat\n");
		exit(2);
	}

	*(s->count) = i;		
	printf("Inicialización %d\n", *(s->count));								
	initqueue(s->blocked);
}

void waitsem(sem *s)
{	
	int pid = getpid();

	*(s->count)--;
	printf("Decremento %d\n", *(s->count));  //Aqui no llega
	if(*(s->count) < 0)
	{
		enqueue(s->blocked, pid);
		kill(pid, SIGSTOP);
	}

}


void signalsem(sem *s)
{
	int pid;

	*(s->count)++;
	if(*(s->count) <= 0)
	{
		pid = dequeue(s->blocked);
		kill(pid, SIGCONT);
	}

}

