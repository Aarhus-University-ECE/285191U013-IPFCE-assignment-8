#include "insertion_sort.h"
#include <stdlib.h>
#include <stdio.h>

int i = 0;
bool sorted(linked_list* llPtr)
{
  if(llPtr->head != NULL)
    {
      node_t* n1 = llPtr->head;
      node_t* n2 = n1->next;

      while(n2 != NULL)
        {
          if(n1->data > n2->data)
            {
              return false;
            }

          else {
            n1 = n1->next;
            n2 = n2->next;
          }
        }
    }
  return true;
}

void sort(linked_list* llPtr)
{
  if(llPtr->head != NULL){
    while(sorted(llPtr) == false){
      node_t* prev = NULL;
      node_t* n1 = llPtr->head;
      node_t* n2 = n1->next;

      while(n2 != NULL)
        {
          if(n1->data > n2->data)
            {
              node_t* left = swap(n1,n2);
              if(prev == NULL)
                {
                  llPtr->head = left;
                  prev=left;
                }
              else
                {
                  prev->next = left;
                  prev = left;
                }
              n1 = left->next;
              n2 = n1->next;
            }
          else {
            prev = n1;
            n1 = n2;
            n2 = n2->next;
          }
        }
    }
  }

}

