#include "list.h"
#include <stdio.h>
#include <stdlib.h>

// Define the structure for List
struct List {
    Node *head;
    Node *tail;
    size_t size;
};

// Define the structure for Node
struct Node {
    Data data;
    struct Node *next;
    // Assuming a doubly-linked list with a previous pointer
    struct Node *prev;
};

// Function to create and initialize a new Node
Node *newNode(Data d) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = d;
        newNode->next = NULL;
        newNode->prev = NULL;
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
        return printf("Node(%p){.data=%d, .prev=%p, .next=%p}", n, ((Node *)n)->data, ((Node *)n)->prev, ((Node *)n)->next);
    }
}

// Function to create and initialize a new List
List *newList() {
    List *newList = (List *)malloc(sizeof(List));
    if (newList != NULL) {
        newList->head = NULL;
        newList->tail = NULL;
        newList->size = 0;
    }
    return newList;
}

// Function to deallocate an existing List
void deleteList(List *l) {
    if (l != NULL) {
        clear(l);
        free(l);
    }
}

// Function to print details of a List
int printList(const void *l) {
    if (l == NULL) {
        return printf("(null)");
    } else {
        return printf("List(%p){.head=%p, .tail=%p, .len=%lu}", l, ((List *)l)->head, ((List *)l)->tail, ((List *)l)->size);
    }
}

// Function to append a Node at the end of the List
List *append(List *l, Node *n) {
    if (l != NULL && n != NULL) {
        if (l->size == 0) {
            // If the list is empty, set head and tail to the new node
            l->head = n;
            l->tail = n;
        } else {
            // Otherwise, update the tail's next pointer and the tail itself
            l->tail->next = n;
            n->prev = l->tail;
            l->tail = n;
        }
        l->size++;
    }
    return l;
}

// Function to clear the contents of a List
void clear(List *l) {
    if (l != NULL) {
        Node *current = l->head;
        Node *next;
        while (current != NULL) {
            next = current->next;
            deleteNode(current);
            current = next;
        }
        l->head = NULL;
        l->tail = NULL;
        l->size = 0;
    }
}

// Function to find a Node in the List based on its data
Node *find(List *l, Data d) {
    if (l != NULL) {
        Node *current = l->head;
        while (current != NULL) {
            if (current->data == d) {
                return current;
            }
            current = current->next;
        }
    }
    return NULL;
}

// Function to insert a Node before a specified position in the List
List *insert(List *l, Node *n, Node *pos) {
    if (l != NULL && n != NULL) {
        if (pos == NULL || pos == l->head) {
            // If pos is NULL or at the head, insert at the beginning
            n->next = l->head;
            if (l->head != NULL) {
                l->head->prev = n;
            }
            l->head = n;
            if (l->size == 0) {
                l->tail = n;
            }
        } else {
            // Otherwise, insert before the specified position
            n->next = pos;
            n->prev = pos->prev;
            pos->prev->next = n;
            pos->prev = n;
        }
        l->size++;
    }
    return l;
}

// Function to get the length (number of nodes) in the List
size_t length(List *l) {
    return (l != NULL) ? l->size : 0;
}

// Function to remove a Node from the List
List *removes(List *l, Node *n) {
    if (l != NULL && n != NULL) {
        if (n->prev != NULL) {
            n->prev->next = n->next;
        } else {
            // If n is the head, update the head
            l->head = n->next;
        }

        if (n->next != NULL) {
            n->next->prev = n->prev;
        } else {
            // If n is the tail, update the tail
            l->tail = n->prev;
        }

        deleteNode(n);
        l->size--;

        // If the list is empty after removal, update the tail as well
        if (l->size == 0) {
            l->tail = NULL;
        }
    }
    return l;
}

// Function to traverse the List and apply a callback function to each node
void traverse(List *l, int (*func)(const void *n)) {
    if (l != NULL && func != NULL) {
        Node *current = l->head;
        while (current != NULL) {
            func(current);
            current = current->next;
        }
    }
}
