#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

extern "C"
{
#include "linked_list.h"
#include "insertion_sort.h"

}

// See Catch2's documentation: https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#scaling-up

TEST_CASE("insertion_sort")
{
    // Test full list with both negative and positive numbers
    linked_list* llPtr = createLinkedList();
    for(int i = 1; i < 4; i++)
    {
        insertFront(createNode(i), llPtr);
    }
    insertFront(createNode(33), llPtr);
    insertFront(createNode(11), llPtr);
    insertFront(createNode(22), llPtr);
    insertFront(createNode(-3), llPtr);

    int testerList[7] = {-3,22,11,33,3,2,1};
    REQUIRE(testerList[0] == llPtr->head->data);
    node* curNode = llPtr->head;
    for (int i = 1; i < 7; ++i)
    {
        REQUIRE(testerList[i] == curNode->next->data);
        curNode = curNode->next;
    }
    
    sort(llPtr);
    
    int sortedList[7] = {-3,1,2,3,11,22,33};
    REQUIRE(sortedList[0] == llPtr->head->data);
    curNode = llPtr->head;
    for (int i = 1; i < 7; ++i)
    {
        REQUIRE(sortedList[i] == curNode->next->data);
        curNode = curNode->next;
    }

    // Test list of size 3
    linked_list* llPtr2 = createLinkedList();
    insertFront(createNode(1), llPtr2);
    insertFront(createNode(-1), llPtr2);
    insertFront(createNode(0), llPtr2);
    int testerList2[3] = {0,-1,1};
    curNode = llPtr2->head;
    REQUIRE(testerList2[0] == curNode->data);
    REQUIRE(testerList2[1] == curNode->next->data);
    REQUIRE(testerList2[2] == curNode->next->next->data);
    sort(llPtr2);
    curNode = llPtr2->head;
    REQUIRE(-1 == curNode->data);
    REQUIRE(0 == curNode->next->data);
    REQUIRE(1 == curNode->next->next->data);

}


TEST_CASE("linked_queue")
{
    // queue q;
    // init_queue(&q);
    // if (!empty(&q)) printf("init not working");
    // enqueue(&q, 47);
    // int y=dequeue(&q);
    // if (y != 47) printf("enqueue/dequeue not working");

}

