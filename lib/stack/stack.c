#include "stack.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


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
int printNode(Node *n) {
    if (n == NULL) {
        return printf("(null)");
    } else {
        return printf("Node(%p){.data=%ld, .next=%p}", n, n->value, n->next);
    }
}

// Function to create and initialize a new Stack
Stack *newStack() {
    Stack *newStack = (Stack *)malloc(sizeof(Stack));
    if (newStack != NULL) {
        newStack->top = NULL;
        newStack->size = 0;
    }
    return newStack;
}

// Function to deallocate an existing Stack
void deleteStack(Stack *s) {
    if (s != NULL) {
        clear(s);
        free(s);
    }
}

// Function to print details of a Stack
int printStack(Stack *s) {
    if (s == NULL) {
        return printf("(null)");
    } else {
        printf("Stack(%p){.top=%p, size=%lu}", s, s->top, (unsigned long)s->size);

        // Print each node in the stack
        Node *current = s->top;
        while (current != NULL) {
            printf(" -> ");
            printNode(current);
            current = current->next;
        }
    }
    return 0;
}

// Function to get the size of the Stack
size_t size(Stack *s) {
    return (s != NULL) ? s->size : 0;
}

// Function to clear the contents of a Stack
void clear(Stack *s) {
    if (s != NULL) {
        Node *current = s->top;
        Node *next;
        while (current != NULL) {
            next = current->next;
            deleteNode(current);
            current = next;
        }
        s->top = NULL;
        s->size = 0;
    }
}

// Function to remove the top element of the Stack
Node *pop(Stack *s) {
    if (s != NULL && s->top != NULL) {
        Node *removedNode = s->top;
        s->top = removedNode->next;
        s->size--;
        return removedNode;
    }
    return NULL;
}

// Function to insert an element at the top of the Stack
Node *push(Stack *s, Data d) {
    if (s != NULL) {
        Node *newNodePtr = newNode(d);
        if (newNodePtr != NULL) {
            newNodePtr->next = s->top;
            s->top = newNodePtr;
            s->size++;
            return newNodePtr;
        }
    }
    return NULL;
}

// Function to get a pointer to the Node at the top of the Stack without popping it
Node *top(Stack *s) {
    return (s != NULL && s->top != NULL) ? s->top : NULL;
}

// Function to traverse the Stack and apply a callback function to each node
void traverse(Stack *s, int (*func)(const void *)) {
    if (s != NULL && func != NULL) {
        Node *current = s->top;
        while (current != NULL) {
            func(current);
            current = current->next;
        }
    }
}