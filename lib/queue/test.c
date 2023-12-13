#include "queue.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestRun.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif // for asprintf
#include <stdio.h>

enum output { SILENT = 0, NORMAL = 1, VERBOSE = 2 };

Queue *_init_queue() {
  Queue *q = NULL;

  if (q = (Queue *)malloc(sizeof(Queue))) {
    // initialize the queue head
    q->head = (Node *)malloc(sizeof(Node));
    q->head->next = NULL;
    q->head->value = 1;

    // add four nodes to the queue
    // queue is now 1 -> 2 -> 3 -> 4 -> 5
    Node *nodeptr;
    Node *temp = q->head;
    for (int i = 2; i <= 5; i++) {
      if (nodeptr = (Node *)malloc(sizeof(Node))) {
        nodeptr->value = (Data)i;
        nodeptr->next = NULL;
        temp->next = nodeptr;
        temp = nodeptr;
      }
    }
    q->tail = nodeptr;

    // set the queue size
    q->size = 5;
  }

  return q;
}

void _final_queue(Queue *q) {
  // Check if the queue isn't valid
  if (q == NULL)
    return;

  // free queue nodes
  Node *temp = q->head;
  while (temp != NULL) {
    temp = temp->next;
    free(q->head);
    q->head = temp;
  }

  // free queue itself
  q->head = NULL;
  q->tail = NULL;
  free(q);
  q = NULL;
}

int _printData(const void *ptr) {
  const Node *node;
  if ((node = (const Node *)ptr)) {
    return printf("%lu ->", node->value);
  } else {
    printf("(nil)");
    return 0;
  }
}

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_queue(void) { return 0; }

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_queue(void) { return 0; }

void testQUEUE(void) { CU_PASS("Queue test suite running ..."); }

void testNEWNODE(void) {
  Node *nodeptr = newNode(42);
  CU_ASSERT_PTR_NOT_NULL_FATAL(nodeptr || "newNode failed");

  CU_ASSERT_EQUAL(nodeptr->value, 42);
  CU_ASSERT_EQUAL(nodeptr->next, NULL);

  free(nodeptr);
  nodeptr = NULL;
}

void testNEWQUEUE(void) {
  Queue *queueptr = newQueue();
  CU_ASSERT_PTR_NOT_NULL_FATAL(queueptr || "newQueue failed");

  CU_ASSERT_EQUAL(queueptr->head, NULL);
  CU_ASSERT_EQUAL(queueptr->tail, NULL);
  CU_ASSERT_EQUAL(queueptr->size, 0);

  _final_queue(queueptr);
  queueptr = NULL;
}

void testBACK(void) {
  Queue *queueptr = _init_queue();
  CU_ASSERT_PTR_NOT_NULL_FATAL(queueptr || "_init_queue failed");
  // Queue is now (head) 1 -> 2 -> 3 -> 4 -> 5 (tail)

  CU_ASSERT_PTR_EQUAL(back(queueptr), queueptr->tail);

  _final_queue(queueptr);
  queueptr = NULL;
}

void testCLEAR(void) {
  Queue *queueptr = _init_queue();
  CU_ASSERT_PTR_NOT_NULL_FATAL(queueptr || "_init_queue failed");
  // Queue is now (head) 1 -> 2 -> 3 -> 4 -> 5 (tail)

  clear(queueptr);
  // Queue is now empty

  CU_ASSERT_PTR_NOT_NULL_FATAL(queueptr);
  CU_ASSERT_PTR_EQUAL(queueptr->head, NULL);
  CU_ASSERT_PTR_EQUAL(queueptr->tail, NULL);
  CU_ASSERT_EQUAL(queueptr->size, 0);

  _final_queue(queueptr);
  queueptr = NULL;
}

void testDEQUEUE(void) {
  Queue *queueptr = _init_queue();
  CU_ASSERT_PTR_NOT_NULL_FATAL(queueptr || "_init_queue failed");
  // Queue is now (head) 1 -> 2 -> 3 -> 4 -> 5 (tail)

  Node *nodeptr = dequeue(queueptr);
  // Queue is now (head) 2 -> 3 -> 4 -> 5 (tail)

  CU_ASSERT_PTR_NOT_NULL_FATAL(nodeptr);
  CU_ASSERT_EQUAL(nodeptr->value, 1);
  CU_ASSERT_EQUAL(queueptr->head->value, 2);
  CU_ASSERT_EQUAL(queueptr->tail->value, 5);
  CU_ASSERT_EQUAL(queueptr->size, 4);

  free(nodeptr);
  nodeptr = NULL;
  _final_queue(queueptr);
  queueptr = NULL;
}

void testENQUEUE(void) {
  Queue *queueptr = _init_queue();
  CU_ASSERT_PTR_NOT_NULL_FATAL(queueptr || "_init_queue failed");
  // Queue is now (head) 1 -> 2 -> 3 -> 4 -> 5 (tail)

  Node *nodeptr = enqueue(queueptr, 6);
  // Queue is now (head) 1 -> 2 -> 3 -> 4 -> 5 -> 6 (tail)

  CU_ASSERT_PTR_NOT_NULL_FATAL(nodeptr);
  CU_ASSERT_PTR_EQUAL(nodeptr, queueptr->tail);
  CU_ASSERT_EQUAL(queueptr->head->value, 1);
  CU_ASSERT_EQUAL(queueptr->tail->value, 6);
  CU_ASSERT_EQUAL(queueptr->size, 6);

  _final_queue(queueptr);
  queueptr = NULL;
}

void testFRONT(void) {
  Queue *queueptr = _init_queue();
  CU_ASSERT_PTR_NOT_NULL_FATAL(queueptr || "_init_queue failed");
  // Queue is now (head) 1 -> 2 -> 3 -> 4 -> 5 (tail)

  CU_ASSERT_PTR_EQUAL(front(queueptr), queueptr->head);

  _final_queue(queueptr);
  queueptr = NULL;
}

void testSIZE(void) {
  Queue *queueptr = _init_queue();
  CU_ASSERT_PTR_NOT_NULL_FATAL(queueptr || "_init_queue failed");
  // Queue is now (head) 1 -> 2 -> 3 -> 4 -> 5 (tail)

  CU_ASSERT_EQUAL(size(queueptr), 5);

  _final_queue(queueptr);
  queueptr = NULL;
}

void testTRAVERSE(void) {
  int retval;
  char *string;
  Queue *queueptr = _init_queue();
  CU_ASSERT_PTR_NOT_NULL_FATAL(queueptr || "_init_queue failed");
  // Queue is now (head) 1 -> 2 -> 3 -> 4 -> 5 (tail)

  if (retval = printQueue(queueptr)) {
    if (!(0 >
          asprintf(&string, "printQueue test passed. Returned %d", retval))) {
      CU_PASS(string);
      free(string);
    }
  }
  traverse(queueptr, &_printData);
  CU_PASS("Traverse test passed.\n");

  _final_queue(queueptr);
  queueptr = NULL;
}

int main(int argc, char *argv[]) {

  /* Parse output option */
  enum output setting = NORMAL;
  for (size_t i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--quiet") == 0 || strcmp(argv[i], "--silent") == 0 ||
        strcmp(argv[i], "-q") == 0)
      setting = SILENT;
    else if (strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-v") == 0)
      setting = VERBOSE;
    else {
    }
  }

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  CU_pSuite pSuite_queue = NULL;
  pSuite_queue =
      CU_add_suite("Suite_Queue", init_suite_queue, clean_suite_queue);
  if (NULL == pSuite_queue) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Add tests to the suite */
  if ((NULL == CU_add_test(pSuite_queue, "test of queues", testQUEUE)) ||
      (NULL == CU_add_test(pSuite_queue, "test of newNode", testNEWNODE)) ||
      (NULL == CU_add_test(pSuite_queue, "test of newQueue", testNEWQUEUE)) ||
      (NULL == CU_add_test(pSuite_queue, "test of back", testBACK)) ||
      (NULL == CU_add_test(pSuite_queue, "test of clear", testCLEAR)) ||
      (NULL == CU_add_test(pSuite_queue, "test of dequeue", testDEQUEUE)) ||
      (NULL == CU_add_test(pSuite_queue, "test of enqueue", testENQUEUE)) ||
      (NULL == CU_add_test(pSuite_queue, "test of front", testFRONT)) ||
      (NULL == CU_add_test(pSuite_queue, "test of size", testSIZE)) ||
      (NULL == CU_add_test(pSuite_queue, "test of traverse", testTRAVERSE)) ||
      (false)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  switch (setting) {
  case SILENT:
    CU_basic_set_mode(CU_BRM_SILENT);
    break;
  case VERBOSE:
    CU_basic_set_mode(CU_BRM_VERBOSE);
    break;
  case NORMAL:
  default:
    CU_basic_set_mode(CU_BRM_NORMAL);
  }
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}