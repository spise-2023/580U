#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <stdint.h>  // uint64_t

#ifndef DATA
#define DATA
typedef uint64_t Data;
#endif // DATA

#ifndef LIST_H
#define LIST_H

typedef struct Node {
  Data data;                // the storage field
  struct Node *next, *prev; // pointers to adjacent nodes
} Node;

typedef struct List {
  Node *head, *tail; // head and tail pointers to the doubly linked list
  size_t size;       // the number of nodes in the list
} List;

Node *newNode(Data d);
void deleteNode(Node *n);
int printNode(const void *n);

List *newList();
void deleteList(List *l);
int printList(const void *l);

List *append(List *l, Node *n);
void clear(List *l);
Node *find(List *l, Data d);
List *insert(List *l, Node *n, Node *pos);
size_t length(List *l);
List *removes(List *l, Node *pos);
void traverse(List *l, int (*func)(const void *));

#endif // LIST_H