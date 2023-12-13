#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Function to create and initialize a new Node
Node *newNode(Data d) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->value = d;
        newNode->next = NULL;
    }
    return newNode;
}

// Function to deallocate an existing Node
void deleteNode(Node *n) {
    free(n);
}

// Function to print details of a Node
int printNode(const void *n) {
    if (n == NULL) {
        return printf("(null)");
    } else {
        const Node *node = (const Node *)n;
        return printf("Node(%p){.value=%lu, .next=%p}", node, node->value, node->next);
    }
}

// Function to create and initialize a new Queue
Queue *newQueue() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue != NULL) {
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
    }
    return queue;
}

// Function to deallocate an existing Queue
void deleteQueue(Queue *q) {
    if (q != NULL) {
        clear(q);
        free(q);
    }
}


// Function to print details of a Queue
int printQueue(const void *q) {
    if (q == NULL) {
        return printf("(null)");
    } else {
        const Queue *queue = (const Queue *)q;
        printf("Queue(%p){.head=%p, .tail=%p, .size=%zu}", queue, queue->head, queue->tail, queue->size);

        // Print each node in the queue
        const Node *current = queue->head;
        while (current != NULL) {
            printf(" -> ");
            printNode(current);
            current = current->next;
        }
        return 0;
    }
}


// Function to get a pointer to the Node at the tail of the Queue without removing it
Node *back(Queue *q) {
    if (q != NULL && q->tail != NULL) {
        return q->tail;  // Return the tail node of the queue
    }
    return NULL;
}


// Function to clear the contents of a Queue
void clear(Queue *q) {
    if (q != NULL) {
        Node *current = q->head;
        Node *next;
        while (current != NULL) {
            next = current->next;
            deleteNode(current);
            current = next;
        }
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
}

// Function to remove the first element of the Queue
Node *dequeue(Queue *q) {
    if (q != NULL && q->head != NULL) {
        Node *removedNode = q->head;
        q->head = removedNode->next;
        if (q->head == NULL) {
            // If the queue becomes empty, update the tail
            q->tail = NULL;
        }
        q->size--;
        return removedNode;
    }
    return NULL;
}
// Function to insert an element at the end of the Queue
Node *enqueue(Queue *q, Data d) {
    if (q != NULL) {
        Node *newNodePtr = newNode(d);  // Use a different name for the variable
        if (newNodePtr != NULL) {
            if (q->tail == NULL) {
                // If the queue is empty, update both head and tail
                q->head = newNodePtr;
                q->tail = newNodePtr;
            } else {
                // Otherwise, update the tail's next pointer
                q->tail->next = newNodePtr;
                q->tail = newNodePtr;
            }
            q->size++;
            return newNodePtr;
        }
    }
    return NULL;
}

// Function to get a pointer to the Node at the head of the Queue without dequeuing it
Node *front(Queue *q) {
    if (q != NULL && q->head != NULL) {
        return q->head;  // Return the head node of the queue
    }
    return NULL;
}

// Function to get the size of the Queue
size_t size(Queue *q) {
    return (q != NULL) ? q->size : 0;
}

// Function to traverse the Queue and apply a callback function to each node
void traverse(Queue *q, int (*func)(const void *)) {
    if (q != NULL && func != NULL) {
        Node *current = q->head;
        while (current != NULL) {
            func(current);
            current = current->next;
        }
    }
}