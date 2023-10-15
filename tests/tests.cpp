#include "catch2/matchers/catch_matchers.hpp"

extern "C" {
#include "insertion_sort.h"
#include "queue.h"
}

TEST_CASE("initialize", "[queue]") {
  queue q;
  initialize(&q);
  REQUIRE(q.front == NULL);
  REQUIRE(q.rear == NULL);
  REQUIRE(q.size == 0);
}

TEST_CASE("empty", "[queue]") {
  queue q;
  q.front = NULL;
  q.rear = NULL;
  q.size = 0;
  REQUIRE(empty(&q));
  node n;
  n.data = 1;
  n.next = NULL;
  q.front = &n;
  q.rear = &n;
  q.size = 1;
  REQUIRE(!empty(&q));
}

TEST_CASE("full", "[queue]") {
  queue q;
  q.front = NULL;
  REQUIRE(!full(&q));
  node n;
  n.data = 1;
  n.next = NULL;
  q.front = &n;
  q.rear = &n;
  q.size = 1;
  REQUIRE(!full(&q));
}

TEST_CASE("enqueue", "[queue]") {
  queue q;
  q.front = NULL;
  q.rear = NULL;
  q.size = 0;
  const int x0 = 1;
  const int x1 = 2;
  enqueue(&q, x0);
  REQUIRE(q.front != NULL);
  REQUIRE(q.rear != NULL);
  REQUIRE(q.front->data == x0);
  REQUIRE(q.size == 1);

  enqueue(&q, x1);
  REQUIRE(q.front != NULL);
  REQUIRE(q.rear != NULL);
  REQUIRE(q.front->data == x0);
  REQUIRE(q.rear->data == x1);
  REQUIRE(q.size == 2);
}


TEST_CASE("dequeue", "[queue]") {
    queue q;
    q.front = NULL;
    q.rear = NULL;
    q.size = 0;
    const int x0 = 1;
    const int x1 = 2;

    node n0;
    n0.data = x0;
    n0.next = NULL;
    node n1;
    n1.data = x1;
    n1.next = NULL;
    // enqueue(&q, x0);
    q.front = &n0;
    q.rear = &n0;
    q.size = 1;

    // enqueue(&q, x1);
    q.rear = &n1;
    q.front->next = &n1;
    q.size = 2;

    const int y0 = dequeue(&q);
    REQUIRE(y0 == x0);
    REQUIRE(q.front != NULL);
    REQUIRE(q.rear != NULL);
    REQUIRE(q.front->data == x1);
    REQUIRE(q.rear->data == x1);
    REQUIRE(q.size == 1);

    const int y1 = dequeue(&q);
    REQUIRE(y1 == x1);
    REQUIRE(q.front == NULL);
    REQUIRE(q.rear == NULL);
    REQUIRE(q.size == 0);
}

TEST_CASE("queue", "[queue]") {
    queue q;
    initialize(&q);
    REQUIRE(empty(&q));
    const int x0 = 2;
    const int x1 = 3;
    enqueue(&q, x0);
    REQUIRE(!empty(&q));
    enqueue(&q, x1);
    REQUIRE(!empty(&q));
    const int y0 = dequeue(&q);
    REQUIRE(!empty(&q));
    const int y1 = dequeue(&q);
    REQUIRE(empty(&q));
    REQUIRE(!full(&q));

    REQUIRE(x0 == y0);
    REQUIRE(x1 == y1);

    int xs[] = {1, 2, 3, 4, 5};
    const int len = sizeof(xs) / sizeof(int);
    for (int i = 0; i < len; i++) {
        enqueue(&q, xs[i]);
    }

    int ys[len];
    for (int i = 0; i < len; i++) {
        ys[i] = dequeue(&q);
    }

    REQUIRE(empty(&q));
    REQUIRE(xs[0] == ys[0]);
    REQUIRE(xs[1] == ys[1]);
    REQUIRE(xs[2] == ys[2]);
    REQUIRE(xs[3] == ys[3]);
    REQUIRE(xs[4] == ys[4]);
}



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

