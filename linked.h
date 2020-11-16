#ifndef linked_h
#define linked_h

#include <stdio.h>

typedef struct _node {
    struct _node* prev;
    struct _node* next;
} Node;

Node* getPrev(Node* node);
Node* getNext(Node* node);
Node* getFirst(Node* node);
Node* getLast(Node* node);

void insertAfter(Node* node, Node* newNode);
void insertBefore(Node* node, Node* newNode);
void insertBeginning(Node* node, Node* newNode);
void insertEnd(Node* node, Node* newNode);

void printNodeList(Node* node, void (*print)(Node* node));
void removeNodeFromList(Node* node);
void removeNodeHard(Node* node);
Node* findNode(Node* node, int (*criteria)(Node* node));
void swapNodes(Node** a, Node** b);
void sortNodes(Node* node, int (*criteria)(Node* a, Node* b));

#endif /* linked_h */
