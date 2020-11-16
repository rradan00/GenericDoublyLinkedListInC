# Generic doubly linked list in C

This is a small c library implementing primitive inheritance and polymorphism to enable the creation of a doubly linked list from any structure in c

**NOTE!** This library is a proof-of-concept, and it's point is to showcase the idea of simple OOP in c, therefore, it expects only **happy cases** in order to make the code as simple and verbose as possible, without, eg. trivial null pointer checks etc. It is not intended for use in other projects. 

## Concept

The library provides a `Node` structure which represents a linked list node, which may be included as a property of any structure in C, symbolically inheriting it.

```c
typedef struct _person {
    Node node;
    char name[STR_SIZE];
} Person;
```

Here, `Person` is an extension of a linked list `Node`, and may be cast as such
```c
Person* person = malloc(sizeof(Person));
// assign data...

Node* personAsNode = (Node*)person;
Node* nextPersonAsNode = personAsNode->next;
Person* nextPerson = (Person*)nextPersonAsNode;
```
The library heavily relies on this feature to treat any child "class" as an extension of the Node "class" which it knows how to manipulate.

This works because `Node` and `Person` both begin in the same memory location, but `Node` is subset of the `Person` memory space, and the compiler can understand it regardless what might follow, whether it's a `Person` structure or something else.

The library also uses **function pointers** to **"override"** functions executed over nodes according to the specifics of the child class in methods like printing and sorting. 

## Methods
Presume for the following examples:
```c
Person* alex = ...;
Person* bob = ...;
Person* charlie = ...;
// etc... where
// Alex -> Bob -> Charlie -> David...
```
Create:
```c
Person* alex = createNode(sizeof(Person));
```
Foreach:
```c
Person* p;
linkedListForeach(p, list){
    printf("%s \n", p->name);
}
```
Basic operators
```c
getNext(bob); // return Charlie
getPrev(bob); // returns Alex
getFirst(walter); // returns Alex
getLast(bob); //returns Zoey
```
List linking
```c
insertAfter(bob, new); // Bob -> new -> Charlie
insertBefore(bob, new); // Alex -> new -> Bob
insertFirst(bob, new); // new -> Alex -> Bob
insertLast(bob, new); // Zoey -> new
```
Print
```c
void printNodeList(Node* node, void (*print)(Node* node)); 
```
```c
printNodeList(bob, printName); // prints "Alex Bob Charlie..."

void printName(Person* person){
   printf("%s ", person->name);
}
```
Remove

```c
removeNodeFromList(bob) //result: Alex -> Charlie -> David
```
Find
```c
Node* findNode(Node* node, int (*criteria)(Node* node));
```
```c
Person* charlie = findNode(alex, isCharlie);

int isCharlie(Person* person){
    return !strcmp(person->name, "Charlie");
}
```
Sort (bubble)
```c
void sortNodes(Node* node, int (*criteria)(Node* a, Node* b));
```
```c
sortNodes(alex, sortPersonsAlphabetically);

int sortPersonsAlphabetically(Person* a, Person* b){
    return strcmp(a->name, b->name) > 0; //swap if b should be ahead of a
}
```

