#include "tree.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Define the data type used in the Node
typedef int Data;

// Define the Node structure
typedef struct Node {
    Data data;
    struct Node *left;
    struct Node *right;
} Node;

// Define the Tree structure
typedef struct Tree {
    Node *root;
} Tree;

// Function to create and initialize a new Node
Node *newNode(Data d) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = d;
        newNode->left = NULL;
        newNode->right = NULL;
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
        return printf("Node(%p){.data=%d, .left=%p, .right=%p}", n, ((Node *)n)->data, ((Node *)n)->left, ((Node *)n)->right);
    }
}

// Function to create and initialize a new Tree
Tree *newTree() {
    Tree *newTree = (Tree *)malloc(sizeof(Tree));
    if (newTree != NULL) {
        newTree->root = NULL;
    }
    return newTree;
}

// Function to deallocate an existing Tree
void deleteTree(Tree *t) {
    if (t != NULL) {
        clearTree(t->root);
        free(t);
    }
}

// Helper function to recursively clear the tree
void clearTree(Node *n) {
    if (n != NULL) {
        clearTree(n->left);
        clearTree(n->right);
        deleteNode(n);
    }
}

// Function to print details of a Tree
int printTree(const void *t) {
    if (t == NULL) {
        return printf("(null)");
    } else {
        printf("Tree(%p)", t);
        // Print each node in the tree using an inorder traversal
        inorderPrint(((Tree *)t)->root);
    }
    return 0;
}

// Helper function to recursively print the tree in inorder
void inorderPrint(Node *n) {
    if (n != NULL) {
        inorderPrint(n->left);
        printf(" -> ");
        printNode(n);
        inorderPrint(n->right);
    }
}

// Function to get the height of the Tree
size_t height(Tree *t) {
    return (t != NULL) ? calculateHeight(t->root) : 0;
}

// Helper function to recursively calculate the height of a node
size_t calculateHeight(Node *n) {
    if (n == NULL) {
        return 0;
    } else {
        size_t leftHeight = calculateHeight(n->left);
        size_t rightHeight = calculateHeight(n->right);
        return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
    }
}

// Function to get the size of the Tree
size_t size(Tree *t) {
    return (t != NULL) ? calculateSize(t->root) : 0;
}

// Helper function to recursively calculate the size of a node
size_t calculateSize(Node *n) {
    if (n == NULL) {
        return 0;
    } else {
        return calculateSize(n->left) + calculateSize(n->right) + 1;
    }
}

// Function to get the depth of a Node in the Tree
size_t depth(Node *n) {
    return (n != NULL) ? calculateDepth(n) : 0;
}

// Helper function to recursively calculate the depth of a node
size_t calculateDepth(Node *n) {
    if (n == NULL) {
        return 0;
    } else {
        size_t leftDepth = calculateDepth(n->left);
        size_t rightDepth = calculateDepth(n->right);
        return (leftDepth > rightDepth) ? leftDepth + 1 : rightDepth + 1;
    }
}

// Function to check if a Node is a leaf
bool isLeaf(Node *n) {
    return (n != NULL && n->left == NULL && n->right == NULL);
}

// Function to find the maximum value Node in the Tree
Node *max(Node *n) {
    return (n != NULL) ? findMax(n) : NULL;
}

// Helper function to recursively find the maximum value Node
Node *findMax(Node *n) {
    while (n->right != NULL) {
        n = n->right;
    }
    return n;
}

// Function to find the minimum value Node in the Tree
Node *min(Node *n) {
    return (n != NULL) ? findMin(n) : NULL;
}

// Helper function to recursively find the minimum value Node
Node *findMin(Node *n) {
    while (n->left != NULL) {
        n = n->left;
    }
    return n;
}

// Function to insert data into the Tree
void insertData(Tree *t, Data d) {
    if (t != NULL) {
        t->root = insert(t->root, d);
    }
}

// Helper function to recursively insert data into the Tree
Node *insert(Node *n, Data d) {
    if (n == NULL) {
        return newNode(d);
    } else {
        if (d < n->data) {
            n->left = insert(n->left, d);
        } else if (d > n->data) {
            n->right = insert(n->right, d);
        }
        return n;
    }
}

// Function to find a Node with a specific data value in the Tree
Node *findData(Tree *t, Data d) {
    return (t != NULL) ? find(t->root, d) : NULL;
}

// Helper function to recursively find a Node with specific data
Node *find(Node *n, Data d) {
    if (n == NULL || n->data == d) {
        return n;
    } else if (d < n->data) {
        return find(n->left, d);
    } else {
        return find(n->right, d);
    }
}

// Function to remove a Node with a specific data value from the Tree
Node *removeData(Tree *t, Data d) {
    if (t != NULL) {
        t->root = removeNode(t->root, d);
    }
    return NULL;
}

// Helper function to recursively remove a Node with specific data
Node *removeNode(Node *n, Data d) {
    if (n == NULL) {
        return NULL;
    } else if (d < n->data) {
        n->left = removeNode(n->left, d);
    } else if (d > n->data) {
        n->right = removeNode(n->right, d);
    } else {
        if (n->left == NULL) {
            Node *temp = n->right;
            deleteNode(n);
            return temp;
        } else if (n->right == NULL) {
            Node *temp = n->left;
            deleteNode(n);
            return temp;
        }
        Node *temp = findMin(n->right);
        n->data = temp->data;
        n->right = removeNode(n->right, temp->data);
    }
    return n;
}

// Function to traverse the Tree in preorder and apply a callback function to each node
void preorder(Tree *t, int (*func)(const void *)) {
    if (t != NULL && func != NULL) {
        preorderTraversal(t->root, func);
    }
}

// Helper function to recursively traverse the Tree in preorder
void preorderTraversal(Node *n, int (*func)(const void *)) {
    if (n != NULL) {
        func(n);
        preorderTraversal(n->left, func);
        preorderTraversal(n->right, func);
    }
}

// Function to traverse the Tree in inorder and apply a callback function to each node
void inorder(Tree *t, int (*func)(const void *)) {
    if (t != NULL && func != NULL) {
        inorderTraversal(t->root, func);
    }
}

// Helper function to recursively traverse the Tree in inorder
void inorderTraversal(Node *n, int (*func)(const void *)) {
    if (n != NULL) {
        inorderTraversal(n->left, func);
        func(n);
        inorderTraversal(n->right, func);
    }
}

// Function to traverse the Tree in postorder and apply a callback function to each node
void postorder(Tree *t, int (*func)(const void *)) {
    if (t != NULL && func != NULL) {
        postorderTraversal(t->root, func);
    }
}

// Helper function to recursively traverse the Tree in postorder
void postorderTraversal(Node *n, int (*func)(const void *)) {
    if (n != NULL) {
        postorderTraversal(n->left, func);
        postorderTraversal(n->right, func);
        func(n);
    }
}
