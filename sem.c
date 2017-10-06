#include <stdio.h>
#include "sem.h"


void initsem(sem *s, int i)
{
	int id = shmget(0x1234, sizeof(s), 0666|IPC_CREAT);		//Obtiene el ID de la memoria
	if(id == -1)
	{
		printf("Error en shmget\n");
		exit(1);
	}

	s = (sem*)shmat(id, NULL, 0);							//Obtiene el apuntador de la memoria
	if(s == NULL)
	{
		printf("Error en shmat\n");
		exit(2);
	}


	*(s->count) = i;										//Inicializa el contador del semáforo (número de procesos en ejecución)
	initqueue(&(s->blocked));
}

void waitsem(sem s)
{
	//Decrementa contador
	//Si es menor que 0 lo manda a bloqueado

	//Si no pues ejecuta

}


void signalsem(sem s)
{
	//Incrementa contador
	//Si es menor 

}

