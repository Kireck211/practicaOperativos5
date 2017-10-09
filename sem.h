#include <stdio.h>
#include "queue.c"

typedef struct semaphore
{
	int count;
	queue *blocked;
}sem;

void waitsem(sem*);
void signalsem(sem*);
//void initsem(sem*, int);



