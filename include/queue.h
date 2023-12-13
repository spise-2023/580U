#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef DATA_T
#define DATA_T
typedef uint64_t Data;
#endif // DATA_T

#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node {
  Data value;
  struct Node *next;
} Node;

typedef struct Queue {
  Node *head, *tail;
  size_t size;
} Queue;

Node *newNode(Data d);
void deleteNode(Node *n);
int printNode(const void *n);

Queue *newQueue();
void deleteQueue(Queue *q);
int printQueue(const void *q);

Node *back(Queue *q);
void clear(Queue *q);
Node *dequeue(Queue *q);
Node *enqueue(Queue *q, Data d);
Node *front(Queue *q);
size_t size(Queue *q);
void traverse(Queue *q, int (*func)(const void *));

#endif // QUEUE_H