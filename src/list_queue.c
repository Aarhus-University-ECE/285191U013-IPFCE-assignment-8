#include "list_queue.h"


void init_queue(queue *q)
{
  q->size = 0;
  q->front = malloc(sizeof(qnode));
  q->rear = malloc(sizeof(qnode));
  q->front->next = q->rear;
  // front -> /empty node/ -> /
}

int empty(queue *q)
{
  return (q->size <= 0);
}

void enqueue(queue *q, int x)
{
  qnode *t = q->front;
  while (t->next != q->rear)
    t = t->next;
  //t points to node just befoe rear
  qnode *tmp = (qnode *)malloc(sizeof(qnode));
  tmp->data = x;
  tmp->next = q->rear; // new node is last
  t->next = tmp;       //previous last is now second last
  q->size = q->size + 1;
}

int dequeue(queue *q)
{
  int x;
  assert(!empty(q));
  qnode *tmp = q->front->next; //tmp point to first, real element
  x = tmp->data;
  q->front->next = tmp->next; //remove tmp from the queue
  free(tmp);
  q->size = q->size - 1; // Added (wait until jens answers if it sohuld be removed)
  return (x);
}
