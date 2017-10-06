#include "queue.h"

void initqueue(queue *q)
{
	q->head=0;
	q->tail=0;
}	

void enqueue(queue *q,int val)
{
	q->elements[q->head]=val;
	// Incrementa al apuntador
	q->head++;
	q->head=q->head%MAXP;
}


int dequeue(queue *q)
{
	int valret;
	valret=q->elements[q->tail];
	// Incrementa al apuntador
	q->tail++;
	q->tail=q->tail%MAXP;
	return(valret);
}

int emptyq(queue *q)
{
	return(q->head==q->tail);
}