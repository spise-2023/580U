#include "tree.h"
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

Tree *gtree = NULL;
Node *nodes[8] = {NULL};
Node *newnodes[4] = {NULL};

///
/// \brief      Initializes the tree.
///
/// \details    Builds a tree with nodes {NULL, 10, 20, 30, 40, 50, 60, 70} and
///             has uninserted newnodes {0, 5, 42, 80} Initializes the tree with
///             the following shape:
///              40
///            /   \
///          20    60
///          / \  /  \
///        10 30 50  70
///
/// Note that because of global storage of nodes[] and newnodes[], there must not
/// ever be two trees initialized by _init_tree at the same time.
///
void _init_tree() {
  
  // Acquire storage for tree
  gtree = (Tree *) malloc(sizeof(Tree));
  gtree->root = NULL;

  // Acquire storage for nodes in tree and initialize values
  for (int i = 1; i < 8; i++) {
    nodes[i] = (Node *)malloc(sizeof(Node));
    nodes[i]->data = ((Data) i * 10);
  }
  // Acquire storage for nodes not in tree and initialize values
  newnodes[0] = (Node *) malloc(sizeof(Node));
  newnodes[0]->data = 0;
  newnodes[1] = (Node *) malloc(sizeof(Node));
  newnodes[1]->data = 5;
  newnodes[2] = (Node *) malloc(sizeof(Node));
  newnodes[2]->data = 42;
  newnodes[3] = (Node *) malloc(sizeof(Node));
  newnodes[3]->data = 80;

  // Build tree
  gtree->root = nodes[4];

  nodes[1]->parent = nodes[2];
  nodes[1]->left = NULL;
  nodes[1]->right = NULL;

  nodes[2]->parent = nodes[4];
  nodes[2]->left = nodes[1];
  nodes[2]->right = nodes[3];

  nodes[3]->parent = nodes[2];
  nodes[3]->left = NULL;
  nodes[3]->right = NULL;

  nodes[4]->parent = NULL;
  nodes[4]->left = nodes[2];
  nodes[4]->right = nodes[6];

  nodes[5]->parent = nodes[6];
  nodes[5]->left = NULL;
  nodes[5]->right = NULL;

  nodes[6]->parent = nodes[4];
  nodes[6]->left = nodes[5];
  nodes[6]->right = nodes[7];

  nodes[7]->parent = nodes[6];
  nodes[7]->left = NULL;
  nodes[7]->right = NULL;
}

//
// \brief      { Finalizes the tree by freeing memory and nullifying the global
//             node pointer arrays. }
//
void _final_tree() {
  // finalize nodes in tree
  for (int i = 1; i < 8; i++) {
    free(nodes[i]);
    nodes[i] = NULL;
  }
  // finalize nodes not in tree
  for (int j = 0; j < 4; j++) {
    free(newnodes[j]);
    newnodes[j] = NULL;
  }

  // finalize tree
  free(gtree);
  gtree = NULL;
}

//
// @brief      {The suite initialization function.}
//
// @return     {Returns 0 on success, non-zero otherwise.}
//
int init_suite_tree(void) { return 0; }

//
// @brief      {The suite cleanup function.}
//
// @return     {Returns 0 on success, non-zero otherwise.}
//
int clean_suite_tree(void) { return 0; }

void testTREE(void) { CU_PASS("Tree test suite running ..."); }

void testNEWNODE(void) {
  Node *nodeptr = newNode(42);
  CU_ASSERT_PTR_NOT_NULL_FATAL(nodeptr && "newNode() failed");

  CU_ASSERT_EQUAL(nodeptr->data, 42);
  CU_ASSERT_EQUAL(nodeptr->parent, NULL);
  CU_ASSERT_EQUAL(nodeptr->left, NULL);
  CU_ASSERT_EQUAL(nodeptr->right, NULL);

  free(nodeptr);
}

void testNEWTREE(void) {
  Tree *treeptr = newTree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(treeptr && "newTree() failed");

  CU_ASSERT_EQUAL(treeptr->root, NULL);

  free(treeptr);
}

void testHEIGHT(void) {
  _init_tree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree && "_init_tree() failed");
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //
  
  // test height of initialized tree
  CU_ASSERT_EQUAL(height(gtree), 2);

  // insert newnodes[0] = 0
  nodes[1]->left = newnodes[0];
  newnodes[0]->parent = nodes[1];
  newnodes[0]->left = NULL;
  newnodes[0]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  CU_ASSERT_EQUAL(height(gtree), 3);

  // insert newnodes[1] = 5
  nodes[1]->left = newnodes[1];
  newnodes[1]->parent = nodes[1];
  newnodes[1]->left = NULL;
  newnodes[1]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  //        \
  //        5
  CU_ASSERT_EQUAL(height(gtree), 4);

  // Insert newnodes[2] = 42
  nodes[5]->left = newnodes[2];
  newnodes[2]->parent = nodes[5];
  newnodes[2]->left = NULL;
  newnodes[2]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /
  //       0     42
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(height(gtree), 4);

  // Insert newnode[3] = 80
  nodes[7]->right = newnodes[3];
  newnodes[3]->parent = nodes[7];
  newnodes[3]->left = NULL;
  newnodes[3]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /    \
  //       0     42    80
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(height(gtree), 4);

  _final_tree();
}

void testSIZE(void) {
  _init_tree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree && "_init_tree() failed");
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //
  
  CU_ASSERT_EQUAL(size(gtree), 7);

  // insert newnodes[0] = 0
  nodes[1]->left = newnodes[0];
  newnodes[0]->parent = nodes[1];
  newnodes[0]->left = NULL;
  newnodes[0]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  CU_ASSERT_EQUAL(size(gtree), 8);

  // insert newnodes[1] = 5
  nodes[1]->left = newnodes[1];
  newnodes[1]->parent = nodes[1];
  newnodes[1]->left = NULL;
  newnodes[1]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(size(gtree), 9);

  // Insert newnodes[2] = 42
  nodes[5]->left = newnodes[2];
  newnodes[2]->parent = nodes[5];
  newnodes[2]->left = NULL;
  newnodes[2]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /
  //       0     42
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(size(gtree), 10);

  // Insert newnode[3] = 80
  nodes[7]->right = newnodes[3];
  newnodes[3]->parent = nodes[7];
  newnodes[3]->left = NULL;
  newnodes[3]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /    \
  //       0     42    80
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(size(gtree), 11);

  _final_tree();
}

void testDEPTH(void) {
  _init_tree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree && "_init_tree() failed");
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //
  
  // test depth of initialized tree
  CU_ASSERT_EQUAL(depth(gtree->root), 0);
  CU_ASSERT_EQUAL(depth(gtree->root->left), 1);
  CU_ASSERT_EQUAL(depth(gtree->root->left->right), 2);

  // insert newnodes[0] = 0
  nodes[1]->left = newnodes[0];
  newnodes[0]->parent = nodes[1];
  newnodes[0]->left = NULL;
  newnodes[0]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  //
  CU_ASSERT_EQUAL(depth(newnodes[0]), 3);

  // insert newnodes[1] = 5
  nodes[1]->left = newnodes[1];
  newnodes[1]->parent = nodes[1];
  newnodes[1]->left = NULL;
  newnodes[1]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(depth(newnodes[1]), 4);

  // Insert newnodes[2] = 42
  nodes[5]->left = newnodes[2];
  newnodes[2]->parent = nodes[5];
  newnodes[2]->left = NULL;
  newnodes[2]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /
  //       0     42
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(depth(newnodes[2]), 3);

  // Insert newnode[3] = 80
  nodes[7]->right = newnodes[3];
  newnodes[3]->parent = nodes[7];
  newnodes[3]->left = NULL;
  newnodes[3]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /    \
  //       0     42    80
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(depth(newnodes[3]), 3);

  _final_tree();
}

void testISLEAF(void) {
  _init_tree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree && "_init_tree() failed");
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  
  // test initialized tree
  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree);
  CU_ASSERT_FALSE(isLeaf(gtree->root));
  CU_ASSERT_FALSE(isLeaf(gtree->root->left));
  CU_ASSERT_TRUE(isLeaf(gtree->root->left->right));

  // insert newnodes[0] = 0
  nodes[1]->left = newnodes[0];
  newnodes[0]->parent = nodes[1];
  newnodes[0]->left = NULL;
  newnodes[0]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  //
  CU_ASSERT_TRUE(isLeaf(newnodes[0]));

  // insert newnodes[1] = 5
  nodes[1]->left = newnodes[1];
  newnodes[1]->parent = nodes[1];
  newnodes[1]->left = NULL;
  newnodes[1]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  //        \
  //        5
  //
  CU_ASSERT_FALSE(isLeaf(newnodes[0]));
  CU_ASSERT_TRUE(isLeaf(newnodes[1]));

  // Insert newnodes[2] = 42
  nodes[5]->left = newnodes[2];
  newnodes[2]->parent = nodes[5];
  newnodes[2]->left = NULL;
  newnodes[2]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /
  //       0     42
  //        \
  //        5
  //
  CU_ASSERT_TRUE(isLeaf(newnodes[2]));

  // Insert newnode[3] = 80
  nodes[7]->right = newnodes[3];
  newnodes[3]->parent = nodes[7];
  newnodes[3]->left = NULL;
  newnodes[3]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /    \
  //       0     42    80
  //        \
  //        5
  //
  CU_ASSERT_TRUE(isLeaf(newnodes[3]));

  _final_tree();
}

void testMAX(void) {
  _init_tree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree && "_init_tree() failed");
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //

  CU_ASSERT_EQUAL(max(gtree->root)->data, 70);
  CU_ASSERT_EQUAL(max(gtree->root->left)->data, 30);
  CU_ASSERT_EQUAL(max(gtree->root->right)->data, 70);

  // insert newnodes[0] = 0
  nodes[1]->left = newnodes[0];
  newnodes[0]->parent = nodes[1];
  newnodes[0]->left = NULL;
  newnodes[0]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  //
  CU_ASSERT_EQUAL(max(gtree->root)->data, 70);
  CU_ASSERT_EQUAL(max(gtree->root->left)->data, 30);
  CU_ASSERT_EQUAL(max(gtree->root->right)->data, 70);

  // insert newnodes[1] = 5
  nodes[1]->left = newnodes[1];
  newnodes[1]->parent = nodes[1];
  newnodes[1]->left = NULL;
  newnodes[1]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(max(gtree->root)->data, 70);
  CU_ASSERT_EQUAL(max(gtree->root->left)->data, 30);
  CU_ASSERT_EQUAL(max(gtree->root->right)->data, 70);

  // Insert newnodes[2] = 42
  nodes[5]->left = newnodes[2];
  newnodes[2]->parent = nodes[5];
  newnodes[2]->left = NULL;
  newnodes[2]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /
  //       0     42
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(max(gtree->root)->data, 70);
  CU_ASSERT_EQUAL(max(gtree->root->left)->data, 30);
  CU_ASSERT_EQUAL(max(gtree->root->right)->data, 70);

  // Insert newnode[3] = 80
  nodes[7]->right = newnodes[3];
  newnodes[3]->parent = nodes[7];
  newnodes[3]->left = NULL;
  newnodes[3]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /    \
  //       0     42    80
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(max(gtree->root)->data, 80);
  CU_ASSERT_EQUAL(max(gtree->root->left)->data, 30);
  CU_ASSERT_EQUAL(max(gtree->root->right)->data, 80);

  _final_tree();
}

void testMIN(void) {
  _init_tree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree && "_init_tree() failed");
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  
  CU_ASSERT_EQUAL(min(gtree->root)->data, 10);
  CU_ASSERT_EQUAL(min(gtree->root->left)->data, 10);
  CU_ASSERT_EQUAL(min(gtree->root->right)->data, 50);

  // insert newnodes[0] = 0
  nodes[1]->left = newnodes[0];
  newnodes[0]->parent = nodes[1];
  newnodes[0]->left = NULL;
  newnodes[0]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  //
  CU_ASSERT_EQUAL(min(gtree->root)->data, 0);
  CU_ASSERT_EQUAL(min(gtree->root->left)->data, 0);
  CU_ASSERT_EQUAL(min(gtree->root->right)->data, 50);

  // insert newnodes[1] = 5
  nodes[1]->left = newnodes[1];
  newnodes[1]->parent = nodes[1];
  newnodes[1]->left = NULL;
  newnodes[1]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(min(gtree->root)->data, 0);
  CU_ASSERT_EQUAL(min(gtree->root->left)->data, 0);
  CU_ASSERT_EQUAL(min(gtree->root->right)->data, 50);

  // Insert newnodes[2] = 42
  nodes[5]->left = newnodes[2];
  newnodes[2]->parent = nodes[5];
  newnodes[2]->left = NULL;
  newnodes[2]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /
  //       0     42
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(min(gtree->root)->data, 0);
  CU_ASSERT_EQUAL(min(gtree->root->left)->data, 0);
  CU_ASSERT_EQUAL(min(gtree->root->right)->data, 42);

  // Insert newnode[3] = 80
  nodes[7]->right = newnodes[3];
  newnodes[3]->parent = nodes[7];
  newnodes[3]->left = NULL;
  newnodes[3]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /    \
  //       0     42    80
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(min(gtree->root)->data, 0);
  CU_ASSERT_EQUAL(min(gtree->root->left)->data, 0);
  CU_ASSERT_EQUAL(min(gtree->root->right)->data, 42);

  _final_tree();
}

void testINSERTDATA(void) {
  _init_tree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree && "_init_tree() failed");
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70

  // insert 0
  insertData(gtree, 0);
  //  Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  //
  CU_ASSERT_EQUAL(gtree->root->left->left->left->data, 0);

  // insert 5
  insertData(gtree, 5);
  // Tree is now:
  //             40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(gtree->root->left->left->left->right->data, 5);

  // insert 42
  insertData(gtree, 42);
  //  Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /
  //       0     42
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(gtree->root->right->left->left->data, 42);

  // insert 80
  insertData(gtree, 80);
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /    \
  //       0     42    80
  //        \
  //        5
  //
  CU_ASSERT_EQUAL(gtree->root->right->right->right->data, 80);

  // Clean up. Note that if deleteTree() is not properly implemented, this test
  // will cause a memory leak because some of the nodes were allocated by calls
  // to insert(). This is the student's responsibility.
  deleteTree(gtree);
  for (int i = 0; i < 8; i++)
    nodes[i] = NULL;
  for (int i = 0; i < 4; i++)
    newnodes[i] = NULL;
}

void testFINDDATA(void) {
  _init_tree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree && "_init_tree() failed");
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  
  CU_ASSERT_PTR_EQUAL(findData(gtree, 40), nodes[4]);
  CU_ASSERT_PTR_EQUAL(findData(gtree, 20), nodes[2]);
  CU_ASSERT_PTR_EQUAL(findData(gtree, 10), nodes[1]);
  CU_ASSERT_PTR_NULL(findData(gtree, 5));

  // insert newnodes[0] = 0
  nodes[1]->left = newnodes[0];
  newnodes[0]->parent = nodes[1];
  newnodes[0]->left = NULL;
  newnodes[0]->right = NULL;

  // insert newnodes[1] = 5
  nodes[1]->left = newnodes[1];
  newnodes[1]->parent = nodes[1];
  newnodes[1]->left = NULL;
  newnodes[1]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0
  //        \
  //        5
  CU_ASSERT_PTR_EQUAL(findData(gtree, 5), newnodes[1]);

  _final_tree();
}

void testREMOVEDATA(void) {
  _init_tree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree && "_init_tree() failed");
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70

  // insert newnodes[0] = 0
  nodes[1]->left = newnodes[0];
  newnodes[0]->parent = nodes[1];
  newnodes[0]->left = NULL;
  newnodes[0]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /
  //       0

  // Delete leaf node (30)
  removeData(gtree, 30);
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          /    /  \
  //        10    50  70
  //        /
  //       0
  CU_ASSERT_PTR_NULL(findData(gtree, 30));
  CU_ASSERT_PTR_NULL(gtree->root->left->right);

  // Delete node with one child (10)
  removeData(gtree, 10);
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          /    /  \
  //         0    50  70
  CU_ASSERT_PTR_NULL(findData(gtree, 30));
  CU_ASSERT_PTR_EQUAL(gtree->root->left->left, newnodes[0]);

  // Delete node with two children (40)
  removeData(gtree, 40);
  // Tree is now:
  //              50
  //            /   \
  //          20    60
  //          /      \
  //         0       70
  CU_ASSERT_PTR_NULL(findData(gtree, 40));
  CU_ASSERT_PTR_EQUAL(gtree->root, nodes[5]);

  _final_tree();
}

void testPREORDER(void) {
  _init_tree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree && "_init_tree() failed");

  // insert newnodes[0] = 0
  nodes[1]->left = newnodes[0];
  newnodes[0]->parent = nodes[1];
  newnodes[0]->left = NULL;
  newnodes[0]->right = NULL;

  // insert newnodes[1] = 5
  nodes[1]->left = newnodes[1];
  newnodes[1]->parent = nodes[1];
  newnodes[1]->left = NULL;
  newnodes[1]->right = NULL;

  // Insert newnodes[2] = 42
  nodes[5]->left = newnodes[2];
  newnodes[2]->parent = nodes[5];
  newnodes[2]->left = NULL;
  newnodes[2]->right = NULL;

  // Insert newnode[3] = 80
  nodes[7]->right = newnodes[3];
  newnodes[3]->parent = nodes[7];
  newnodes[3]->left = NULL;
  newnodes[3]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /    \
  //       0     42    80
  //        \
  //        5
  //

  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree);
  CU_PASS("Verify preorder traversal visits: 40 20 10 0 5 30 60 50 42 70 80");
  printTree((const void *)gtree);
  inorder(gtree, &printNode);

  _final_tree();
}

void testINORDER(void) {
  _init_tree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree && "_init_tree() failed");

  // insert newnodes[0] = 0
  nodes[1]->left = newnodes[0];
  newnodes[0]->parent = nodes[1];
  newnodes[0]->left = NULL;
  newnodes[0]->right = NULL;

  // insert newnodes[1] = 5
  nodes[1]->left = newnodes[1];
  newnodes[1]->parent = nodes[1];
  newnodes[1]->left = NULL;
  newnodes[1]->right = NULL;

  // Insert newnodes[2] = 42
  nodes[5]->left = newnodes[2];
  newnodes[2]->parent = nodes[5];
  newnodes[2]->left = NULL;
  newnodes[2]->right = NULL;

  // Insert newnode[3] = 80
  nodes[7]->right = newnodes[3];
  newnodes[3]->parent = nodes[7];
  newnodes[3]->left = NULL;
  newnodes[3]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /    \
  //       0     42    80
  //        \
  //        5
  //

  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree);
  CU_PASS("Verify preorder traversal visits: 0 5 10 20 30 40 42 50 60 70 80");
  printTree((const void *)gtree);
  inorder(gtree, &printNode);

  _final_tree();
}

void testPOSTORDER(void) {
  _init_tree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree && "_init_tree() failed");

  // insert newnodes[0] = 0
  nodes[1]->left = newnodes[0];
  newnodes[0]->parent = nodes[1];
  newnodes[0]->left = NULL;
  newnodes[0]->right = NULL;

  // insert newnodes[1] = 5
  nodes[1]->left = newnodes[1];
  newnodes[1]->parent = nodes[1];
  newnodes[1]->left = NULL;
  newnodes[1]->right = NULL;

  // Insert newnodes[2] = 42
  nodes[5]->left = newnodes[2];
  newnodes[2]->parent = nodes[5];
  newnodes[2]->left = NULL;
  newnodes[2]->right = NULL;

  // Insert newnode[3] = 80
  nodes[7]->right = newnodes[3];
  newnodes[3]->parent = nodes[7];
  newnodes[3]->left = NULL;
  newnodes[3]->right = NULL;
  // Tree is now:
  //              40
  //            /   \
  //          20    60
  //          / \  /  \
  //        10 30 50  70
  //        /     /    \
  //       0     42    80
  //        \
  //        5
  //

  CU_ASSERT_PTR_NOT_NULL_FATAL(gtree);
  CU_PASS("Verify postorder traversal visits: 5 0 10 30 20 42 50 80 70 60 40");
  printTree((const void *)gtree);
  inorder(gtree, &printNode);

  _final_tree();
}

int main(int argc, char *argv[]) {

  // Parse output option */
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

  // initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  // add a suite to the registry */
  CU_pSuite pSuite_tree = NULL;
  pSuite_tree = CU_add_suite("Suite_Tree", init_suite_tree, clean_suite_tree);
  if (NULL == pSuite_tree) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Add tests to the suite */
  if ((NULL == CU_add_test(pSuite_tree, "test of trees", testTREE)) ||
      (NULL == CU_add_test(pSuite_tree, "test of newNode", testNEWNODE)) ||
      (NULL == CU_add_test(pSuite_tree, "test of newTree", testNEWTREE)) ||
      (NULL == CU_add_test(pSuite_tree, "test of height", testHEIGHT)) ||
      (NULL == CU_add_test(pSuite_tree, "test of size", testSIZE)) ||
      (NULL == CU_add_test(pSuite_tree, "test of depth", testDEPTH)) ||
      (NULL == CU_add_test(pSuite_tree, "test of isLeaf", testISLEAF)) ||
      (NULL == CU_add_test(pSuite_tree, "test of max", testMAX)) ||
      (NULL == CU_add_test(pSuite_tree, "test of min", testMIN)) ||
      (NULL == CU_add_test(pSuite_tree, "test of insertData", testINSERTDATA)) ||
      (NULL == CU_add_test(pSuite_tree, "test of findData", testFINDDATA)) ||
      (NULL == CU_add_test(pSuite_tree, "test of removeData", testREMOVEDATA)) ||
      (NULL == CU_add_test(pSuite_tree, "test of preorder traversal", testPREORDER)) ||
      (NULL == CU_add_test(pSuite_tree, "test of inorder traversal", testINORDER)) ||
      (NULL == CU_add_test(pSuite_tree, "test of postorder traversal", testPOSTORDER)) ||
      (false)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Run all tests using the CUnit Basic interface */
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