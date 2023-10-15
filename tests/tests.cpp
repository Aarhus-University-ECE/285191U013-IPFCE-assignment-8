#include "catch2/matchers/catch_matchers.hpp"

extern "C" {
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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

node *ll_create_node(int x) {
  node *n = (node *)malloc(sizeof(node));
  if (!n) {
    fprintf(stderr, "%s:%d Allocation with malloc() failed.\n", __FILE__,
            __LINE__);
    exit(1);
  }

  n->data = x;
  n->next = NULL;

  return n;
}

void ll_append(node *head, int x) {
    assert(head != NULL);
    node* p = head;
    while (p->next != NULL) {
        p = p->next;
    }

    node* n = ll_create_node(x);
    p->next = n;
}

node* ll_from_array(const int *array, const int len) {
    node* list = (node *)malloc(sizeof(node));
    if (!list) {
        fprintf(stderr, "%s:%d Allocation with malloc() failed.\n", __FILE__,
                __LINE__);
        exit(1);
    }
    list->next = NULL;

    for (int i = 0; i < len; i++) {
        ll_append(list, array[i]);
    }

    return list;
}

int ll_size(node *head) {
    assert(head != NULL);
    
    int size = 0;
    while (head != NULL) {
        head = head->next;
        size++;
    }

    return size - 1; // The first node is the head (a sentinel)
}

int* ll_to_array(node *head) {
    assert(head != NULL);
    const int len = ll_size(head);
    int *arr = (int *)malloc(sizeof(int) * len);
    if (!arr) {
        fprintf(stderr, "%s:%d Allocation with malloc() failed.\n", __FILE__,
                __LINE__);
        exit(1);
    }

    int i = 0;
    node* p = head->next; // The first node is the head (a sentinel)
    while (p != NULL) {
        arr[i] = p->data;
        i++;
        p = p->next;
    }
    
    return arr;
}

bool arrays_equal(const int *arr1, const int *arr2, const int len) {
    assert(arr1 != NULL);
    assert(arr2 != NULL);
    assert(len > 0);

    for (int i = 0; i < len; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}


TEST_CASE("positive-numbers", "[insertion_sort]") {
    const int input[] =        {5, 22, 11, 33, 3, 2, 1};
    const int len = sizeof(input) / sizeof(int);
    const int input_sorted[len] = {1, 2, 3, 5, 11, 22, 33};

    node* list = ll_from_array(input, len);
    isort(list);
    int* arr = ll_to_array(list);
    REQUIRE(arrays_equal(arr, input_sorted, len));
}

TEST_CASE("negative-numbers", "[insertion_sort]") {
    const int input[] =        {-5, -22, -11, -33, -3, -2, -1};
    const int len = sizeof(input) / sizeof(int);
    const int input_sorted[len] = {-33, -22, -11, -5, -3, -2, -1};

    node* list = ll_from_array(input, len);
    isort(list);
    int* arr = ll_to_array(list);
    REQUIRE(arrays_equal(arr, input_sorted, len));
}

TEST_CASE("2-numbers", "[insertion_sort]") {
    const int input[] =        {1, 10};
    const int len = sizeof(input) / sizeof(int);
    const int input_sorted[len] = {1, 10};

    node* list = ll_from_array(input, len);
    isort(list);
    int* arr = ll_to_array(list);
    REQUIRE(arrays_equal(arr, input_sorted, len));
}

TEST_CASE("numbers", "[insertion_sort]") {
    const int input[] = { 3, 5, 11, 2, 16, 18, 6, 4, -14, 9, -7, 20, 10, 19, 8, 1, 17, 13, 15, -12 };
    const int len = sizeof(input) / sizeof(int);
    const int input_sorted[] = { -14, -12, -7, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 13, 15, 16, 17, 18, 19, 20 };

    node* list = ll_from_array(input, len);
    isort(list);
    int* arr = ll_to_array(list);
    REQUIRE(arrays_equal(arr, input_sorted, len));
}

