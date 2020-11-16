#include <stdlib.h>
#include "linked.h"

Node* getPrev(Node* node){
    return node->prev;
}

Node* getNext(Node* node){
    return node->next;
}

Node* getFirst(Node* node){
    if(node->prev)
        return getFirst(node->prev);
    else return node;
}

Node* getLast(Node* node){
    if(node->next)
        return getLast(node->next);
    else return node;
}

void insertAfter(Node* node, Node* newNode){
    Node* alreadyAfter = node->next;
    if(alreadyAfter) {
        newNode->next = alreadyAfter;
        alreadyAfter->prev = newNode;
    }
    node->next = newNode;
    newNode->prev = node;
}

void insertBefore(Node* node, Node* newNode){
    if(node->prev) {
        Node* alreadyBefore = node->prev;
        newNode->prev = alreadyBefore;
        alreadyBefore->next = newNode;
    }
    node->prev = newNode;
    newNode->next = node;
}


void insertBeginning(Node* node, Node* newNode){
    if(node->prev)
        return insertBeginning(node->prev, newNode);
    else {
        newNode->next = node;
        node->prev = newNode;
    }
}

void insertEnd(Node* node, Node* newNode){
    if(node->next)
        return insertBeginning(node->next, newNode);
    else {
        node->next = newNode;
        newNode->prev = node;
    }
}

void printNodeList(Node* node, void (*printNode)(Node* node)){
    node = getFirst(node);
    while(node){
        printNode(node);
        node = node->next;
    }
}

void removeNodeFromList(Node* node){
    Node* prev = node->prev;
    Node* next = node->next;
    if(prev && next) {
        prev->next = next;
        next->prev = prev;
    } else if (prev){
        prev->next = NULL;
    } else if (next){
        next->prev = NULL;
    }
    
    free(node);
}

void removeNodeHard(Node* node){
    if(node->prev)
        node->prev->next = NULL;
    if(node->next)
        node->next->prev = NULL;
    free(node);
}

Node* findNode(Node* node, int (*criteria)(Node* node)){
    if(!node)
        return NULL;
    if(criteria(node))
        return node;
    Node* prev = node->prev;
    Node* next = node->next;
    while(prev || next){
        if(prev && criteria(prev))
            return prev;
        if(next && criteria(next))
            return next;
        if(prev)
            prev = prev->prev;
        if(next)
            next = next->next;
    }
    return NULL;
}


void _swapAdjacent(Node* a, Node* b){
    Node* prev = a->prev;
    Node* next = b->next;
    b->next = a;
    a->prev = b;
    if(prev)
        prev->next = b;
    b->prev = prev;
    if(next)
        next->prev = a;
    a->next = next;
}

void _swapSeperated(Node* a, Node* b){
    Node* prevA = a->prev;
    Node* nextA = a->next;
    Node* prevB = b->prev;
    Node* nextB = b->next;
    
    if(prevA)
        prevA->next = b;
    b->prev = prevA;
    
    if(nextA)
        nextA->prev = b;
    b->next = nextA;
    
    if(prevB)
        prevB->next = a;
    a->prev = prevB;
    
    if(nextB)
        nextB->prev = a;
    a->next =nextB;
}

void swapNodes(Node** a, Node** b){
    if((*a)->next == *b && (*b)->prev == *a)
        _swapAdjacent(*a, *b);
    else
        _swapSeperated(*a, *b);
    
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

//bubble sort
void sortNodes(Node* node, int (*criteria)(Node* a, Node* b)){
    Node* start = getFirst(node);
    int swapped = 1;
    while(start->next && swapped){
        swapped = 0;
        Node* a = start;
        Node* b = start->next;
        while(a->next){
            if(criteria(a, b)) {
                swapNodes(&a, &b);
                swapped = 1;
            }
            a = a->next;
            b = b->next;
        }
        start = start->next;
    }
}
