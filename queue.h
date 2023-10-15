#pragma once

#include <stdbool.h>

#include "node.h"
 
typedef struct queue {
  int size;
  node *front;
  node *rear;
} queue;

void initialize(queue *q);
bool empty(queue *q);
bool full(queue *q);
void enqueue(queue *q, int x);
int dequeue(queue *q);
