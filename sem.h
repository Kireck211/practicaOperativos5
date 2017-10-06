#include <stdio.h>
#include "queue.c"

typedef struct semaphore
{
	int *count;
	queue blocked;
}sem;

void waitsem(sem s);
void signalsem(sem s);
void initsem(sem *s, int i);



