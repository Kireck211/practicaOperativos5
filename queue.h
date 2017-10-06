#define MAXP 100

typedef struct _queue{
	int elements[MAXP];
	int head;
	int tail;
}queue;

void initqueue(queue *q);
void enqueue(queue *q,int val);
int dequeue(queue *q);
int emptyq(queue *q);