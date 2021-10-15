#ifndef __LINKED_LIST_H_
#define __LINKED_LIST_H_
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
  int data;
  struct node *next;
} node_t;

typedef struct
{
  node_t *head;
} linked_list;

node_t *createNode(int value);
linked_list *createLinkedList();
void insertFront(node_t *nodePtr, linked_list *llPtr);
node_t *swap(node_t *x, node_t *y);
bool isempty();
void printLL(linked_list *llPtr);

#endif // __LINKED_LIST_H_
