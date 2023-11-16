#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef DATA_T
#define DATA_T 
typedef uint64_t Data;
#endif // DATASTRUCTS_DATA_T

#ifndef TREE_H
#define TREE_H

typedef struct Node {
	Data data;
	struct Node *parent;
	struct Node *left;
	struct Node *right;
} Node;

typedef struct Tree {
	Node *root;
} Tree;

// Node constructor/destructors
Node *newNode(Data d);
void deleteNode(Node *n);
int printNode(const void *n);

// Tree constructor/destructors
Tree *newTree();
void deleteTree(Tree *t);
int printTree(const void *t);

// Tree properties
size_t height(Tree *t);
size_t size(Tree *t);
size_t depth(Node *n);
bool isLeaf(Node *n);
Node *max(Node *n);
Node *min(Node *n);

// Tree mutators/accessors
void insertData(Tree *t, Data d);
Node *findData(Tree *t, Data d);
Node *removeData(Tree *t, Data d);

// Traversal Routines
void preorder(Tree *t, int (*func)(const void *));
void inorder(Tree *t, int (*func)(const void *));
void postorder(Tree *t, int (*func)(const void *));

#endif // DATASTRUCTS_TREE_H 