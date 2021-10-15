#include "linked_list.h"

node_t *createNode(int value)
{
  node_t *nodePtr = malloc(sizeof(node_t));
  nodePtr->data = value;
  nodePtr->next = NULL;
  return nodePtr;
}

linked_list *createLinkedList()
{
  linked_list *llPtr = malloc(sizeof(linked_list));
  llPtr->head = NULL;
  return llPtr;
}

void insertFront(node_t *nodePtr, linked_list *llPtr)
{
  nodePtr->next = llPtr->head;
  llPtr->head = nodePtr;
}

node_t *swap(node_t *x, node_t *y)
{
  x->next = y->next;
  y->next = x;
  return y;
}
bool isempty(linked_list *llPtr)
{
  return llPtr->head != NULL;
}
void printLL(linked_list *llPtr)
{
  node_t *n = llPtr->head;
  while (n != NULL)
  {
    printf("| %d ", n->data);
    n = n->next;
  }
  printf("|\n");
}
