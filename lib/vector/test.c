#include "vector.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestRun.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum output { SILENT = 0, NORMAL = 1, VERBOSE = 2 };

/**
 * @brief      Initializes a vector by allocating storage and setting fields to
 *             known values.
 *
 * @param      vecptr  A pointer to a vector to be initialized.
 *
 * @details    It is caller's responsibility to free vecptr.
 *
 * @return     { Returns a pointer to the initialized vector. }
 */
Vector *_init_vector() {
  Vector *vecptr = (Vector *) malloc(sizeof(Vector));
  vecptr->size = 3;
  vecptr->capacity = 4;
  vecptr->array = (Data *)malloc(4 * sizeof(Data));
  for (int i = 0; i < 3; i++) {
    vecptr->array[i] = i + 1;
  }
  vecptr->array[3] = 0;

  // Vector is now {.size=3,.capacity=4,.array={1,2,3,0}}
  return vecptr;
}

/**
 * @brief      Finalizes a vector by freeing storage and setting fields to
 * nullptr
 *
 * @param      vecptr  The vecptr
 */
void _final_vector(Vector *vecptr) {
  vecptr->size = 0;
  vecptr->capacity = 0;
  free(vecptr->array);
  vecptr->array = NULL;
  free(vecptr);
  vecptr = NULL;
}

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_vector(void) { return 0; }

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_vector(void) { return 0; }

void testVECTOR(void) { CU_PASS("Vector test suite running..."); }

void testNEWVECTOR(void) {
  Vector *vectorptr = NULL;

  vectorptr = newVector(4);
  CU_ASSERT_PTR_NOT_NULL_FATAL(vectorptr);
  CU_ASSERT_PTR_NOT_NULL_FATAL(vectorptr->array);
  for (int i = 0; i < 4; i++) {
    CU_ASSERT_EQUAL(vectorptr->array[i], 0);
  }
  CU_ASSERT_EQUAL(vectorptr->size, 0);
  CU_ASSERT_EQUAL(vectorptr->capacity, 4);

  free(vectorptr->array);
  vectorptr->array = NULL;
  free(vectorptr);
  vectorptr = NULL;
}

void testDELETEVECTOR(void) {
  Vector *vectorptr = _init_vector();
  CU_ASSERT_PTR_NOT_NULL_FATAL(vectorptr || "_init_vector() failed");

  deleteVector(vectorptr);
  CU_PASS("Vector deleted. Check valgrind for no memory leaks.");
}

void testPRINTVECTOR(void) {
  Vector *vectorptr = _init_vector();
  CU_ASSERT_PTR_NOT_NULL_FATAL(vectorptr || "_init_vector() failed");

  // Print the expected output
  printf("Expected: Vector(%p){.size=%lu,.array={", vectorptr, vectorptr->size);
  for (int i = 0; i < vectorptr->size; i++) {
    printf("%lu,", vectorptr->array[i]);
  }
  printf("}\n");

  // Print the actual output
  int retval;
  printf("Actual: ");
  retval = printVector(vectorptr);
  printf("\n");
  CU_ASSERT(retval > 0);
  CU_PASS("Comparison to see if printVector worked");

  _final_vector(vectorptr);
}

void testAT(void) {
  Vector *vectorptr = _init_vector();
  CU_ASSERT_PTR_NOT_NULL_FATAL(vectorptr || "_init_vector() failed");
  
  Data *dptr = NULL;
  Data expected[4] = {1ULL, 2ULL, 3ULL, 0ULL};

  // Index in bounds
  for (int i = 0; i < 3; ++i) {
    dptr = at(vectorptr, i);
    CU_ASSERT_EQUAL(*dptr, expected[i]);
  }

  // Index out of bounds but not beyond capacity
  dptr = at(vectorptr, 3);
  CU_ASSERT_PTR_NULL(dptr);

  // Index out of bounds and beyond capacity
  dptr = at(vectorptr, 4);
  CU_ASSERT_PTR_NULL(dptr);

  _final_vector(vectorptr);
}

void testCLEAR(void) {
  Vector *vectorptr = _init_vector();
  CU_ASSERT_PTR_NOT_NULL_FATAL(vectorptr || "_init_vector() failed");

  clear(vectorptr);
  CU_ASSERT_PTR_NOT_NULL_FATAL(vectorptr);
  CU_ASSERT_EQUAL(vectorptr->size, 0);
  CU_ASSERT_EQUAL(vectorptr->capacity, 4);
  CU_ASSERT_PTR_NOT_NULL_FATAL(vectorptr->array);
  for (int i = 0; i < 4; i++) {
    CU_ASSERT_EQUAL(vectorptr->array[i], 0);
  }

  _final_vector(vectorptr);
}

void testFIND(void) {
  Vector *vectorptr = _init_vector();
  CU_ASSERT_PTR_NOT_NULL_FATAL(vectorptr || "_init_vector() failed");

  // Find in array
  Data *dptr = NULL;
  dptr = find(vectorptr, 3);
  CU_ASSERT_PTR_NOT_NULL(dptr);
  if (dptr != NULL) {
    CU_ASSERT_EQUAL(*dptr, 3ULL);
  }

  // Not in array
  dptr = &vectorptr->array[0];
  dptr = find(vectorptr, 4);
  CU_ASSERT_PTR_NULL(dptr);

  _final_vector(vectorptr);
}

void testINSERT(void) {
  Vector *vectorptr = _init_vector();
  CU_ASSERT_PTR_NOT_NULL_FATAL(vectorptr || "_init_vector() failed");

  // Insertion in bounds (no expansion required)
  insert(vectorptr, 4ULL, 3);
  CU_ASSERT_EQUAL(vectorptr->array[3], 4ULL);
  CU_ASSERT_EQUAL(vectorptr->size, 4);
  CU_ASSERT_EQUAL(vectorptr->capacity, 4);

  // Insertion out of bounds (expansion required)
  insert(vectorptr, 5ULL, 4);
  CU_ASSERT_EQUAL(vectorptr->array[4], 5ULL);
  CU_ASSERT_EQUAL(vectorptr->size, 5);
  CU_ASSERT_EQUAL(vectorptr->capacity, 8);

  _final_vector(vectorptr);
}

void testRESIZE(void) {
  Data expected[8] = {1ULL, 2ULL, 3ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL};
  Vector *vectorptr = _init_vector();
  CU_ASSERT_PTR_NOT_NULL_FATAL(vectorptr || "_init_vector() failed");

  vectorptr=resize(vectorptr,8);
  CU_ASSERT_EQUAL(vectorptr->size, 3);
  CU_ASSERT_EQUAL(vectorptr->capacity, 8);
  for (int i = 0; i < 8; i++) {
    CU_ASSERT_EQUAL(vectorptr->array[i], expected[i]); 
  }
  _final_vector(vectorptr);
}

void testREMOVES(void) { 
  Data *retptr = NULL;
  Vector *vectorptr = _init_vector();
  CU_ASSERT_PTR_NOT_NULL_FATAL(vectorptr || "_init_vector() failed");
  // Vector is now {.size=3,.capacity=4,.array={1,2,3,0}}

  // Remove in bounds, at middle of array
  retptr = removes(vectorptr, 1);
  // ...now .array={1,3,0,0}, .size=2 
  CU_ASSERT_PTR_NOT_NULL(retptr);
  if (retptr != NULL) {
    CU_ASSERT_EQUAL(*retptr, 3);
  }
  CU_ASSERT_EQUAL(vectorptr->size, 2);
  
  Data expected1[4] = {1ULL, 3ULL, 0ULL, 0ULL};
  CU_ASSERT_EQUAL(vectorptr->capacity, 4);
  for (int i = 0; i < 4; i++) {
      CU_ASSERT_EQUAL(vectorptr->array[i], expected1[i]);
  }
  
  // Remove in bounds at end of array,
  retptr = removes(vectorptr, 1);
  // Now .array={1,0,0,0}, .size=1
  CU_ASSERT_PTR_NOT_NULL(retptr);
  if (retptr != NULL) {
    CU_ASSERT_EQUAL(*retptr, 0);
  }
  CU_ASSERT_EQUAL(vectorptr->size, 1);
  
  Data expected2[4] = {1ULL, 0ULL, 0ULL, 0ULL};
  CU_ASSERT_EQUAL(vectorptr->capacity, 4);
  for (int i = 0; i < 4; i++) {
      CU_ASSERT_EQUAL(vectorptr->array[i], expected2[i]);
  }

  // Remove in bounds at beginning of array,
  retptr = removes(vectorptr, 0);
  // ... now .array={0,0,0,0}, .size=0
  CU_ASSERT_PTR_NOT_NULL(retptr);
  if (retptr != NULL) {
    CU_ASSERT_EQUAL(*retptr, 0);
  }
  CU_ASSERT_EQUAL(vectorptr->size, 0);
  CU_ASSERT_EQUAL(vectorptr->capacity, 4);
  
  Data expected3[4] = {0ULL, 0ULL, 0ULL, 0ULL};
  for (int i = 0; i < 4; i++) {
      CU_ASSERT_EQUAL(vectorptr->array[i], expected3[i]);
  }

  // Remove out of bounds
  retptr = removes(vectorptr, 4);
  CU_ASSERT_PTR_NULL(retptr);

  _final_vector(vectorptr);
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
  CU_pSuite pSuite_vector = NULL;
  pSuite_vector =
      CU_add_suite("Suite_Vector", init_suite_vector, clean_suite_vector);
  if (NULL == pSuite_vector) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Add tests to the suite */
  if ((NULL == CU_add_test(pSuite_vector, "test of vector type", testVECTOR)) ||
    (NULL == CU_add_test(pSuite_vector, "test of newVector function", testNEWVECTOR)) ||
    (NULL == CU_add_test(pSuite_vector, "test of deleteVector function", testDELETEVECTOR)) ||
    (NULL == CU_add_test(pSuite_vector, "test of at function", testAT)) ||
    (NULL == CU_add_test(pSuite_vector, "test of clear function", testCLEAR)) ||
    (NULL == CU_add_test(pSuite_vector, "test of find function", testFIND)) ||
    (NULL == CU_add_test(pSuite_vector, "test of insert function", testINSERT)) ||
    (NULL == CU_add_test(pSuite_vector, "test of resize function", testRESIZE)) ||
    (NULL == CU_add_test(pSuite_vector, "test of removes function", testREMOVES)) ||
    (NULL == CU_add_test(pSuite_vector, "test of printVector function", testPRINTVECTOR)) ||
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