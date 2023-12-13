#include "list.h"
#include <stdio.h>
#include <stdlib.h>

Node *newNode(Data d) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = d;
        newNode->next = NULL;
        newNode->prev = NULL;
    }
    return newNode;
}

void deleteNode(Node *n) {
    free(n);
}

int printNode(const void *n) {
    if (n == NULL) {
        return printf("(null)\n");
    } else {
        Node *node = (Node *)n;
        return printf("Node(%p){.data=%ld, .prev=%p, .next=%p}\n", node, node->data, node->prev, node->next);
    }
}

List *newList() {
    List *newList = (List *)malloc(sizeof(List));
    if (newList != NULL) {
        newList->head = NULL;
        newList->tail = NULL;
        newList->size = 0;
    }
    return newList;
}

void deleteList(List *l) {
    clear(l);
    free(l);
}

int printList(const void *l) {
    if (l == NULL) {
        return printf("(null)\n");
    } else {
        List *list = (List *)l;
        return printf("List(%p){.head=%p, .tail=%p, .len=%lu}\n", list, list->head, list->tail, list->size);
    }
}

List *append(List *l, Node *n) {
    if (l == NULL || n == NULL) return l;
    if (l->tail == NULL) {
        l->head = n;
        l->tail = n;
        n->prev = NULL;
    } else {
        l->tail->next = n;
        n->prev = l->tail;
        l->tail = n;
    }
    n->next = NULL;
    l->size++;
    return l;
}

void clear(List *l) {
    if (l == NULL) return;
    Node *current = l->head;
    while (current != NULL) {
        Node *next = current->next;
        deleteNode(current);
        current = next;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}

Node *find(List *l, Data d) {
    if (l == NULL) return NULL;
    Node *current = l->head;
    while (current != NULL) {
        if (current->data == d) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

List *insert(List *l, Node *n, Node *pos) {
    if (l == NULL || n == NULL) return l;
    if (pos == NULL || pos == l->head) {
        n->next = l->head;
        if (l->head != NULL) {
            l->head->prev = n;
        }
        l->head = n;
        if (l->tail == NULL) {
            l->tail = n;
        }
    } else {
        n->next = pos;
        n->prev = pos->prev;
        if (pos->prev != NULL) {
            pos->prev->next = n;
        }
        pos->prev = n;
    }
    l->size++;
    return l;
}

size_t length(List *l) {
    return (l != NULL) ? l->size : 0;
}

List *removes(List *l, Node *n) {
    if (l == NULL || n == NULL) return l;
    if (n->prev != NULL) {
        n->prev->next = n->next;
    } else {
        l->head = n->next;
    }
    if (n->next != NULL) {
        n->next->prev = n->prev;
    } else {
        l->tail = n->prev;
    }
    deleteNode(n);
    l->size--;
    return l;
}

void traverse(List *l, int (*func)(const void *n)) {
    if (l == NULL || func == NULL) return;
    Node *current = l->head;
    while (current != NULL) {
        func(current);
        current = current->next;
    }
}
