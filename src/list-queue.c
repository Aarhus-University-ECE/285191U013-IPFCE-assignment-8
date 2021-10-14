#include <stdio.h>
#include <malloc.h>
#include <assert.h>

typedef struct node {
  int data;
  struct node* next;
} node;

typedef struct queue {
  int size;
  node *front;
  node *rear;
} queue;

void init_queue(queue *q)
{
    q->size  = 0;
    q->front = malloc(sizeof(node));
    q->rear = malloc(sizeof(node));
    q->front->next = q->rear;
    // front -> /empty node/ -> /
}

int empty(queue *q)
{
   return (q->size <= 0);
}

void enqueue(queue *q, int x)
{
    node *t = q->front;
    while (t->next !=q->rear)
      t = t->next;
    //t points to node just befoe rear
    node *tmp = (node *) malloc(sizeof(node));
    tmp->data = x;
    tmp->next = q->rear; // new node is last
    t->next = tmp; //previous last is now second last
    q->size = q->size + 1;
 }

int dequeue(queue *q)
{
    int x;
    assert(!empty(q));
    node *tmp = q->front->next;  //tmp point to first, real element
    x = tmp->data;
    q->front->next = tmp ->next; //remove tmp from the queue
    free(tmp);
    return(x);
}

int main(void) {
    queue q;
    init_queue(&q);
    if (!empty(&q)) printf("init not working");
    enqueue(&q, 47);
    int y=dequeue(&q);
    if (y != 47) printf("enqueue/dequeue not working");
    printf("%d", y);
   return 0;
}