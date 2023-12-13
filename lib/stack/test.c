#include "stack.h"
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

Stack *_init_stack() {
  Stack *s = NULL;
  if (s = (Stack *)malloc(sizeof(Stack))) {
    // Initialize bottom of stack
    // stack is now (top) 1
    s->top = (Node *)malloc(sizeof(Node));
    s->top->value = 1;
    s->top->next = NULL;

    // Add four nodes to the stack
    // stack is now (top) 5->4->3->2->1
    for (int i = 2; i <= 5; i++) {
      Node *temp = (Node *)malloc(sizeof(Node));
      temp->value = i;
      temp->next = s->top;
      s->top = temp;
    }

    // Set the stack size
    s->size = 5;
  }

  return s;
}

void _final_stack(Stack *s) {
  // Check if the stack isn't valid
  if (s == NULL)
    return; // Stack is empty

  // Traverse the stack from top to bottom
  Node *temp = s->top;
  while (s->top != NULL) {
    temp = s->top;
    s->top = s->top->next;
    free(temp);
  }

  // Free the stack itself
  s->top = NULL;
  free(s);
  s = NULL;
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
int init_suite_stack(void) { return 0; }

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_stack(void) { return 0; }

void testSTACK(void) { CU_PASS("Stack test suite running ..."); }

void testNEWNODE(void) {
  Node *nodeptr = newNode(42);
  CU_ASSERT_PTR_NOT_NULL_FATAL(nodeptr || "newNode failed");
  CU_ASSERT_EQUAL(nodeptr->value, 42);
  CU_ASSERT_EQUAL(nodeptr->next, NULL);

  free(nodeptr);
  nodeptr = NULL;
}

void testNEWSTACK(void) {
  Stack *stackptr = newStack();
  CU_ASSERT_PTR_NOT_NULL_FATAL(stackptr || "newStack failed");

  CU_ASSERT_EQUAL(stackptr->top, NULL);
  CU_ASSERT_EQUAL(stackptr->size, 0);

  _final_stack(stackptr);
}

void testCLEAR(void) {
  Stack *stackptr = _init_stack();
  CU_ASSERT_PTR_NOT_NULL_FATAL(stackptr || "_init_stack failed");
  // Stack is now (top) 5->4->3->2->1

  clear(stackptr);
  // Stack is now (top)(nil)

  CU_ASSERT_PTR_NOT_NULL_FATAL(stackptr);
  CU_ASSERT_EQUAL(stackptr->top, NULL);
  CU_ASSERT_EQUAL(stackptr->size, 0);

  _final_stack(stackptr);
}

void testSIZE(void) {
  Stack *stackptr = _init_stack();
  CU_ASSERT_PTR_NOT_NULL_FATAL(stackptr || "_init_stack failed");
  // Stack is now (top) 5->4->3->2->1

  CU_ASSERT_EQUAL(size(stackptr), 5);

  _final_stack(stackptr);
}

void testTOP(void) {
  Stack *stackptr = _init_stack();
  CU_ASSERT_PTR_NOT_NULL_FATAL(stackptr || "_init_stack failed");
  // Stack is now (top) 5->4->3->2->1

  CU_ASSERT_PTR_EQUAL(top(stackptr), stackptr->top);

  _final_stack(stackptr);
}

void testPOP(void) {
  Stack *stackptr = _init_stack();
  CU_ASSERT_PTR_NOT_NULL_FATAL(stackptr || "_init_stack failed");
  // Stack is now (top) 5->4->3->2->1

  Node *nodeptr = pop(stackptr);
  // Stack is now (top) 4->3->2->1

  CU_ASSERT_PTR_NOT_NULL_FATAL(nodeptr);
  CU_ASSERT_EQUAL(nodeptr->value, 5);
  CU_ASSERT_EQUAL(stackptr->top->value, 4);
  CU_ASSERT_EQUAL(stackptr->size, 4);

  free(nodeptr);
  _final_stack(stackptr);
}

void testPUSH(void) {
  Stack *stackptr = _init_stack();
  CU_ASSERT_PTR_NOT_NULL_FATAL(stackptr || "_init_stack failed");
  // Stack is now (top) 5->4->3->2->1

  Node *temp = stackptr->top;
  Node *nodeptr = push(stackptr, 6);
  // Stack is now (top) 6->5->4->3->2->1

  CU_ASSERT_PTR_NOT_NULL_FATAL(nodeptr);
  CU_ASSERT_PTR_EQUAL(nodeptr, stackptr->top);
  CU_ASSERT_PTR_EQUAL(nodeptr->next, temp);
  CU_ASSERT_EQUAL(stackptr->top->value, 6);
  CU_ASSERT_EQUAL(stackptr->size, 6);

  _final_stack(stackptr);
}

void testTRAVERSE(void) {
  int retval;
  char *string;
  Stack *stackptr = _init_stack();
  CU_ASSERT_PTR_NOT_NULL_FATAL(stackptr || "_init_stack failed");
  // Stack is now (top) 5->4->3->2->1

  if (retval = printStack(stackptr)) {
    if (!(0 >
          asprintf(&string, "printStack test passed. Returned %d", retval))) {
      CU_PASS(string);
      free(string);
    }
  }
  traverse(stackptr, &_printData);
  CU_PASS("Traverse test passed.\n");

  _final_stack(stackptr);
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
  CU_pSuite pSuite_stack = NULL;
  pSuite_stack =
      CU_add_suite("Suite_Stack", init_suite_stack, clean_suite_stack);
  if (NULL == pSuite_stack) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Add tests to the suite */
  if ((NULL == CU_add_test(pSuite_stack, "test of stack", testSTACK)) ||
      (NULL == CU_add_test(pSuite_stack, "test of newNode", testNEWNODE)) ||
      (NULL == CU_add_test(pSuite_stack, "test of newStack", testNEWSTACK)) ||
      (NULL == CU_add_test(pSuite_stack, "test of clear", testCLEAR)) ||
      (NULL == CU_add_test(pSuite_stack, "test of size", testSIZE)) ||
      (NULL == CU_add_test(pSuite_stack, "test of top", testTOP)) ||
      (NULL == CU_add_test(pSuite_stack, "test of pop", testPOP)) ||
      (NULL == CU_add_test(pSuite_stack, "test of push", testPUSH)) ||
      (NULL == CU_add_test(pSuite_stack, "test of traverse", testTRAVERSE)) ||
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