#ifndef __LIST_QUEUE_H_
#define __LIST_QUEUE_H_
#include <assert.h>
#include <stdlib.h>

typedef struct qnode
{
  int data;
  struct qnode *next;
} qnode;

typedef struct queue
{
  int size;
  qnode *front;
  qnode *rear;
} queue;


void init_queue(queue *q);
int empty(queue *q);
void enqueue(queue *q, int x);
int dequeue(queue *q);


#endif // __LIST_QUEUE_H_