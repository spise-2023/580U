#include "tree.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Node constructor/destructors
Node *newNode(Data d) {

    Node *n=(Node *) malloc(sizeof(Node));
	if(n!=NULL){
		n->data=d;
		n->parent=NULL;
		n->left=NULL;
		n->right=NULL;
		return n;
	}

  return NULL;
}
void deleteNode(Node *n) {
    if(n!=NULL){
	    n->parent=NULL;
		n->left=NULL;
		n->right=NULL;
		free(n);
	    n=NULL;
	}
  return;
}

int printNode(const void *n) {
    if (n != NULL) {
        const Node *node = (const Node *)n;
        printf("Node data: %d\n", node->data);
        return 1; 
    }
    return 0;
}

// Tree constructor/destructors
Tree *newTree() {
     Tree *t=(Tree *) malloc(sizeof(Tree));
	if(t!=NULL){
		t->root=NULL;
		return t;
	}
  return NULL;
}


void deleteTree(Tree *t) {

   if (t != NULL && t->root != NULL) {
        Node* stack[100];
        int top = -1;

        stack[++top] = t->root;

        while (top >= 0) {
            Node* current = stack[top--];

            if (current->right != NULL) {
                stack[++top] = current->right;
            }

            if (current->left != NULL) {
                stack[++top] = current->left;
            }

            free(current);
        }

        t->root = NULL; 
    }
}

    // Recursive function to print the tree
    void printTNode(const Node* node) {
        if (node != NULL) {
            printf("%ld ", node->data);
            printTNode(node->left);
            printTNode(node->right);
        }
    }

// Function to print the entire tree
int printTree(const void* t) {
    if (t == NULL) {
        return 0; 
    }
    const Tree* tree = (const Tree*)t;

    printTNode(tree->root);

    return 1;
};

// Tree properties

//helper function to find height.
size_t countHeight(Node* root) {
    if (root==NULL)
        return 0;
    else {
        size_t left = countHeight(root->left);
        size_t right = countHeight(root->right);
        if (left >= right)
            return left + 1;
        else
            return right + 1;
    }
}

size_t height(Tree *t) {
    if(t==NULL)
        return 0; 
    return countHeight(t->root);
}

//helper function to count size
size_t countSize(Node* root) {
    if (root==NULL)
        return 0;
    else {
        size_t left = countSize(root->left);
        size_t right = countSize(root->right);
            return left + right + 1;
    }
}
 
size_t size(Tree *t) {
    if(t==NULL)
        return 0; 
    return countSize(t->root);
}
 
size_t depth(Node *n) {
    if(n==NULL)
        return 0;
    else if(n->parent==NULL)
        return 0; 
    size_t currentDepth = depth(n->parent);
    return currentDepth + 1;
 }  

 
bool isLeaf(Node *n) {
    if(n==NULL)
        return false;
    if(n->left==NULL && n->right==NULL)
        return true;
    return false;
     }
 
Node *max(Node *n) {
    if(n==NULL)
        return NULL; 
    if(n->right==NULL)
        return n;
    return max(n->right);
}
 
Node *min(Node *n) {
    if(n==NULL)
        return NULL; 
    if(n->left==NULL)
        return n;
    return min(n->left);
   }

// Tree mutators/accessors

//helper function insertNode to insert in insertData.
void insertNode(Node *n, Data d){
    if(d<n->data){
        if(n->left==NULL){
            Node *nwNode=newNode(d);
            n->left=nwNode;
            nwNode->parent=n;
        }
        else
           insertNode(n->left, d); 
    }
    else if(d>n->data){
        if(n->right==NULL){
            Node *nwNode=newNode(d);
            n->right=nwNode;
            nwNode->parent=n;
        }
        else
           insertNode(n->right, d); 
    }
}

void insertData(Tree *t, Data d) {
    if(t==NULL)
        return; 
    else if(t->root==NULL)
        t->root=newNode(d);
    else
        insertNode(t->root, d);
}
 
Node *findData(Tree *t, Data d) {
    if (t == NULL || t->root == NULL) {
        return NULL; 
    }

    Node* current = t->root;

    while (current != NULL) {
        if (d == current->data) {
            return current;
        } else if (d < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL; 
}

//helper function to help in removeData
void removeLeaf(Node *n){
    if(n->parent->right==n)
        n->parent->right=NULL;
    else
        n->parent->left=NULL;
}

//helper function to help in removeData
void shortCircuit(Node *n){
    if(n->parent->right==n){
            if(n->right==NULL){
                n->parent->right=n->left;
                n->left->parent=n->parent;
            }
            else{
                n->parent->right=n->right;
                n->right->parent=n->parent;
            }
        }
        else{
            if(n->right==NULL){
                n->parent->left=n->left;
                n->left->parent=n->parent;
            }
            else{
                n->parent->left=n->right;
                n->right->parent=n->parent;
            }
        }
}

//helper function to help in removeData
void promotion(Node *n){
    Node *minNode=min(n->right);
    n->data=minNode->data;
    if(minNode->left==NULL && minNode->right==NULL)
        removeLeaf(minNode);
    else
        shortCircuit(minNode);
}

Node *removeData(Tree *t, Data d) {
    Node *n=findData(t,d);
    if(n==NULL)
        return NULL; 
    else if(isLeaf(n)){
        if(n==t->root)
            t->root=NULL;
        else
            removeLeaf(n);
    }
        
    else if(n->left==NULL || n->right==NULL)
        shortCircuit(n);
    else if(n->left!=NULL && n->right!=NULL)
        promotion(n);
    return n;
 }
 

// Traversal Routines
void preorderHelper(Node *n, int (*func)(const void *)) {
    if (n == NULL)
        return;
    func(n->data);
    preorderHelper(n->left, func);
    preorderHelper(n->right, func);
}

void preorder(Tree *t, int (*func)(const void *)) {
    if (t == NULL || t->root == NULL)
        return;
    func(t->root->data);
    preorderHelper(t->root->left, func);
    preorderHelper(t->root->right, func);
}

void inorderHelper(Node *n, int (*func)(const void *)) {
    if (n != NULL) {
        inorderHelper(n->left, func);
        func(&n->data);
        inorderHelper(n->right, func);
    }
}

void inorder(Tree *t, int (*func)(const void *)) {
    if (t == NULL || t->root == NULL)
        return;
    inorderHelper(t->root, func);
}

void postorderHelper(Node *n, int (*func)(const void *)) {
    if (n != NULL) {
        postorderHelper(n->left, func);
        postorderHelper(n->right, func);
        func(&n->data);
    }
}

void postorder(Tree *t, int (*func)(const void *)) {
    if (t == NULL || t->root == NULL)
        return;
    postorderHelper(t->root, func);
}