#include "list.h"
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

List *_init_list() {
  List *list = NULL;
  if (list = (List *) malloc(sizeof(List))){
    // initialize the list head
    list->head = (Node *) malloc(sizeof(Node));
    list->head->data = 1;
    list->head->prev = NULL;
    list->head->next = NULL;
    list->tail = list->head;

    // add four nodes to the list
    for (int i = 2; i <= 5; i++) {
      list->tail->next = (Node *)malloc(sizeof(Node));
      list->tail->next->data = i;
      list->tail->next->prev = list->tail;
      list->tail->next->next = NULL;
      list->tail = list->tail->next;
    }

    // Set list size
    list->size = 5;
  }

  return list;
}

void _final_list(List *list) {
  if (list) {
    Node *curr = list->head;
    Node *next;

    while (curr != NULL) {
      next = curr->next;
      free(curr);
      curr = next;
    }

    free(list);
    list = NULL;
  }
}

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_list(void) { return 0; }

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_list(void) { return 0; }

void testLIST(void) { CU_PASS("List test suite running..."); }

void testNEWNODE(void) {
  Node *nodeptr = newNode(42ULL);
  CU_ASSERT_PTR_NOT_NULL(nodeptr || "newNode() failed");

  CU_ASSERT_EQUAL(42ULL, nodeptr->data);
  CU_ASSERT_PTR_NULL(nodeptr->next);
  CU_ASSERT_PTR_NULL(nodeptr->prev);

  free(nodeptr);
  nodeptr = NULL;
}

void testNEWLIST(void) {
  List *listptr = newList();
  CU_ASSERT_PTR_NOT_NULL(listptr || "newList() failed");

  CU_ASSERT_EQUAL(0, listptr->size);
  CU_ASSERT_PTR_NULL(listptr->head);
  CU_ASSERT_PTR_NULL(listptr->tail);

  free(listptr);
  listptr = NULL;
}

void testAPPEND(void) {
  Node *nodeptr = NULL;
  List *listptr = _init_list();
  CU_ASSERT_PTR_NOT_NULL_FATAL(listptr || "_init_list() failed");
  // list is now 1 -> 2 -> 3 -> 4 -> 5

  nodeptr = (Node *)malloc(sizeof(Node));
  if (nodeptr) {
    nodeptr->data = 6ULL;
  }
  append(listptr, nodeptr);
  // list is now 1 -> 2 -> 3 -> 4 -> 5 -> 6

  CU_ASSERT_PTR_NOT_EQUAL(listptr->head, nodeptr);
  CU_ASSERT_PTR_EQUAL(listptr->tail, nodeptr);
  CU_ASSERT_EQUAL(listptr->size, 6);
  CU_ASSERT_EQUAL(listptr->head->data, 1ULL);
  CU_ASSERT_EQUAL(listptr->tail->data, 6ULL);

  _final_list(listptr);
  listptr = NULL;
}

void testCLEAR(void) {
  List *listptr = _init_list();
  CU_ASSERT_PTR_NOT_NULL_FATAL(listptr || "_init_list() failed");

  clear(listptr);
  CU_ASSERT_PTR_NULL(listptr->head);
  CU_ASSERT_PTR_NULL(listptr->tail);
  CU_ASSERT_EQUAL(listptr->size, 0);

  _final_list(listptr);
  listptr = NULL;
}

void testFIND(void) {
  List *listptr = _init_list();
  CU_ASSERT_PTR_NOT_NULL_FATAL(listptr || "_init_list() failed");

  CU_ASSERT_PTR_EQUAL(find(listptr, 1ULL), listptr->head);
  CU_ASSERT_PTR_EQUAL(find(listptr, 2ULL), listptr->head->next);
  CU_ASSERT_PTR_EQUAL(find(listptr, 5ULL), listptr->tail);
  CU_ASSERT_PTR_NULL(find(listptr, 6ULL));

  _final_list(listptr);
  listptr = NULL;
}

void testINSERT(void) {
  List *listptr = _init_list();
  CU_ASSERT_PTR_NOT_NULL_FATAL(listptr || "_init_list() failed");
  // list is now 1 -> 2 -> 3 -> 4 -> 5

  Node *nodeptr10 = (Node *)malloc(sizeof(Node));
  if (nodeptr10) {
    nodeptr10->data = 10ULL;
    nodeptr10->next = NULL;
    nodeptr10->prev = NULL;
  }

  Node *nodeptr20 = (Node *)malloc(sizeof(Node));
  if (nodeptr20) {
    nodeptr20->data = 20ULL;
    nodeptr20->next = NULL;
    nodeptr20->prev = NULL;
  }

  insert(listptr, nodeptr20, listptr->head->next->next);
  // list is now 1 -> 2 -> 20 -> 3 -> 4 -> 5

  CU_ASSERT_EQUAL(listptr->size, 6);
  CU_ASSERT_PTR_EQUAL(listptr->head->next->next, nodeptr20);
  CU_ASSERT_EQUAL(listptr->head->next->next->data, nodeptr20->data);
  CU_ASSERT_PTR_EQUAL(listptr->head->next->next->next, nodeptr20->next);
  CU_ASSERT_PTR_EQUAL(listptr->head->next, nodeptr20->prev);

  insert(listptr, nodeptr10, listptr->head);
  // list is now 10 -> 1 -> 2 -> 20 -> 3 -> 4 -> 5

  CU_ASSERT_EQUAL(listptr->size, 7);
  CU_ASSERT_PTR_EQUAL(listptr->head, nodeptr10);
  CU_ASSERT_EQUAL(listptr->head->data, nodeptr10->data);
  CU_ASSERT_PTR_EQUAL(listptr->head->next, nodeptr10->next);
  CU_ASSERT_PTR_NULL(listptr->head->prev);

  _final_list(listptr);
  listptr = NULL;
}

void testLENGTH(void) {
  List *listptr = _init_list();
  CU_ASSERT_PTR_NOT_NULL_FATAL(listptr || "_init_list() failed");
  // list is now 1 -> 2 -> 3 -> 4 -> 5

  CU_ASSERT_EQUAL(length(listptr), 5);
  _final_list(listptr);
  listptr = NULL;
}

void testREMOVES(void) {
  List *listptr = _init_list();
  CU_ASSERT_PTR_NOT_NULL_FATAL(listptr || "_init_list() failed");
  // list is now 1 -> 2 -> 3 -> 4 -> 5

  Node *newhead = listptr->head->next;
  removes(listptr, listptr->head);
  // list is now 2 -> 3 -> 4 -> 5
  CU_ASSERT_EQUAL(listptr->size, 4);
  CU_ASSERT_PTR_EQUAL(listptr->head, newhead);

  _final_list(listptr);
  listptr = NULL;
}

void testTRAVERSE(void) {
  int retval;
  char *string;
  List *listptr = _init_list();
  CU_ASSERT_PTR_NOT_NULL_FATAL(listptr || "_init_list() failed");
  // list is now 1 -> 2 -> 3 -> 4 -> 5

  if (retval = printList(listptr)) {
    if (!(0 >
          asprintf(&string, "printList test passed. Returned %d", retval))) {
      CU_PASS(string);
      free(string);
    }
  }
  traverse(listptr, &printNode);
  CU_PASS("\nTraverse test passed.\n");

  _final_list(listptr);
  listptr = NULL;
}

void testPRINTNODE(void) {
  int retval;
  char *string;
  Node *nodeptr = (Node *)malloc(sizeof(Node));
  if (nodeptr) {
    nodeptr->data = 42ULL;
    nodeptr->next = NULL;
    nodeptr->prev = NULL;
  }
  CU_ASSERT_PTR_NOT_NULL_FATAL(nodeptr || "malloc() failed");

  if ((retval = printNode(nodeptr))) {
    if (!(0 >
          asprintf(&string, "printNode test passed. Returned %d", retval))) {
      CU_PASS(string);
      free(string);
    }
  } else
    CU_FAIL("printNode test failed.");

  free(nodeptr);
  nodeptr = NULL;
}

void testPRINTLIST(void) {
  int retval;
  char *string;
  List *listptr = _init_list();
  CU_ASSERT_PTR_NOT_NULL_FATAL(listptr || "_init_list() failed");
  // list is now 1 -> 2 -> 3 -> 4 -> 5

  if ((retval = printList(listptr))) {
    if (!(0 >
          asprintf(&string, "printList test passed. Returned %d", retval))) {
      CU_PASS(string);
      free(string);
    }
  } else
    CU_FAIL("printList test failed.");

  _final_list(listptr);
  listptr = NULL;
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
  CU_pSuite pSuite_list = NULL;
  pSuite_list = CU_add_suite("Suite_List", init_suite_list, clean_suite_list);
  if (NULL == pSuite_list) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Add tests to the suite */
  if ((NULL == CU_add_test(pSuite_list, "test of lists", testLIST)) ||
      (NULL ==
       CU_add_test(pSuite_list, "test of newNode function", testNEWNODE)) ||
      (NULL ==
       CU_add_test(pSuite_list, "test of newList function", testNEWLIST)) ||
      (NULL ==
       CU_add_test(pSuite_list, "test of append function", testAPPEND)) ||
      (NULL == CU_add_test(pSuite_list, "test of clear function", testCLEAR)) ||
      (NULL == CU_add_test(pSuite_list, "test of find function", testFIND)) ||
      (NULL ==
       CU_add_test(pSuite_list, "test of insert function", testINSERT)) ||
      (NULL ==
       CU_add_test(pSuite_list, "test of length function", testLENGTH)) ||
      (NULL ==
       CU_add_test(pSuite_list, "test of removes function", testREMOVES)) ||
      (NULL ==
       CU_add_test(pSuite_list, "test of traverse function", testTRAVERSE)) ||
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