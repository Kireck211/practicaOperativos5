#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "sem.h"

extern int errno;

void initsem(sem initialized_s, int i)
{
	int sem_id, count_id, queue_id;
	int errnum;
	sem * s;

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
	s = (sem*)shmat(sem_id, NULL, 0);						//Obtiene el apuntador de la memoria
	if(s == NULL)
	{
		printf("Error en shmat\n");
		exit(2);
	}
	*s = initialized_s;

	//Inicialización de memoria para sem.count
	count_id = shmget(0x1235, sizeof(int), 0666|IPC_CREAT);
	if(count_id == -1)
	{
		printf("Error en shmget\n");
		exit(1);
	}
	s->count = (int*)shmat(count_id, NULL, 0);
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
	s->blocked = (queue*)shmat(queue_id, NULL, 0);
	if(s->blocked == NULL)
	{
		printf("Error en shmat\n");
		exit(2);
	}

	*(s->count) = i;
	initqueue(s->blocked);
	printf("count: %p\n", s->count);
}

void waitsem(sem *s)
{	
	int pid = getpid();
	//printf("Aqui todavía llea int pid = getpid() (waitsem)\n");
	s->count--;
	//printf("Aqui si llega s->count--; (waitsem)\n");
	//printf("El proceso es: %d y count es: %d\n", pid, *(s->count));
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

