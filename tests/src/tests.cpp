#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <assert.h>

extern "C"
{
#include "linked_list.h"
#include "insertion_sort.h"
#include "list_queue.h"

}

// See Catch2's documentation: https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#scaling-up

// For testing purposes only
linked_list* convertArrayToLinkedList(int array[], int arraySize)
{
    linked_list* llPtr = createLinkedList();
    for (int i = 0; i < arraySize; ++i)
    {
        insertFront(createNode(array[arraySize-i-1]), llPtr);
    }
    return llPtr;
}
// For testing purposes only
void convertLinkedListToArray(linked_list* llPtr, int arr[])
{
    // Create array from linked list
    node* curNode = llPtr->head;
    int i = 0;
    while(curNode != NULL)
    {
        arr[i++] = curNode->data;
        curNode = curNode->next;
    }
}
// For testing purposes only
bool compareArrays(int arr1[], int arr2[], int arrSize)
{
    for (int i = 0; i < arrSize; ++i)
    {
        if (arr1[i] != arr2[i])
            return false;
    }
    return true;
}
// For testing purposes only
void testLinkedListInsertionSort(int randomArray[], int sortedArray[], int linkedListArray[], int arraySize)
{
    linked_list * llPtr = convertArrayToLinkedList(randomArray, arraySize);
    convertLinkedListToArray(llPtr, linkedListArray);
    assert(compareArrays(randomArray, linkedListArray, arraySize) == true); // checks array and linked list are equal
    sort(llPtr);
    convertLinkedListToArray(llPtr, linkedListArray);
    REQUIRE(compareArrays(sortedArray, linkedListArray, arraySize) == true); // check sorted array and sorted linked list are equal

}



TEST_CASE("insertion_sort")
{
    // Test full random list
    int testerList[7] = {-3,22,11,33,3,2,1};
    int sortedList[7] = {-3,1,2,3,11,22,33};
    int linkedListArray[7];
    testLinkedListInsertionSort(testerList, sortedList, linkedListArray, 7);


    // Test list with both negative and positive numbers
    int testerList2[3] = {0,-1,1};
    int sortedList2[3] = {-1,0,1};
    int linkedListArray2[3];
    testLinkedListInsertionSort(testerList2, sortedList2, linkedListArray2, 3);


    // Test list with duplicate values
    int testerList3[10] = {6,6,5,4,2,3,3,3,2,1};
    int sortedList3[10] = {1,2,2,3,3,3,4,5,6,6};
    int linkedListArray3[10];
    testLinkedListInsertionSort(testerList3, sortedList3, linkedListArray3, 10);
}


TEST_CASE("linked_queue")
{
    // Test inserting random values into queue and check size
    int valuesToInsert[4] = {-5,10,0,5};
    queue qq;
    init_queue(&qq);
    int queueSize = 0;
    REQUIRE(empty(&qq) == 1);
    for (int i = 0; i < 4; ++i)
    {
        enqueue(&qq, valuesToInsert[i]);
        REQUIRE(qq.size == ++queueSize);
    }

    // Test empty function with empty queue
    queue q;
    init_queue(&q);
    REQUIRE(empty(&q) == 1);

    // Test empty function with non-empty queue
    queue q1;
    init_queue(&q1);
    enqueue(&q1, 5);
    REQUIRE(empty(&q1) == 0);
    dequeue(&q1);
    REQUIRE(empty(&q1) == 1); 

    // Test enqueue then dequeue
    enqueue(&q1,-5);
    enqueue(&q1,10);
    enqueue(&q1,0);
    enqueue(&q1,5);
   

    REQUIRE(-5 == dequeue(&q1));
    REQUIRE(10 == dequeue(&q1));
    REQUIRE(0 == dequeue(&q1));
    REQUIRE(5 == dequeue(&q1));

}

