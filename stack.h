#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef DATA_T
#define DATA_T
typedef uint64_t Data;
#endif // DATA_T

#ifndef STACK_H
#define STACK_H

typedef struct Node {
  Data value;
  struct Node *next;
} Node;

typedef struct Stack {
  Node *top;
  size_t size;
} Stack;

Node *newNode(Data d);
void deleteNode(Node *n);
int printNode(Node *n);

Stack *newStack();
void deleteStack(Stack *s);
int printStack(Stack *s);

void clear(Stack *s);
size_t size(Stack *l);
Node *top(Stack *s);
Node *pop(Stack *s);
Node *push(Stack *s, Data d);
void traverse(Stack *s, int (*func)(const void *));

#endif // STACK_H