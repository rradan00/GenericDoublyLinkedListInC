#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked.h"

#define STR_SIZE 256

typedef struct _person {
    Node node;
    char name[STR_SIZE];
} Person;

Person* newPerson(char name[256]);
void printPerson(Person* person);
int sortPersonsAlphabetically(Person* a, Person* b);
int isCharlie(Person* person);

int main(int argc, const char * argv[]) {
    
    Person* alex    = newPerson("Alex");
    Person* bob     = newPerson("Bob");
    Person* charlie = newPerson("Charlie");
    Person* david   = newPerson("David");
    
    //alternative method
    Person* eric    = createNode(sizeof(Person));
    strcpy(eric->name, "Eric");
    
    /*
        Set up list as follows:
        Bob <-> Alex <-> Eric <-> Charlie <-> David
    */
    insertAfter(bob, alex);
    insertAfter(alex, eric);
    insertAfter(eric, charlie);
    insertAfter(charlie, david);
    
    /*
        Example manual print implementation
        (can use printNodeList from library)
    */
    Person* person = getFirst(eric);
    printf("Manual print:\n");
    while(person){
        printf("%s\n", person->name);
        person = getNext(person);
    }
    printf("\n");

    printf("Library print:\n");
    printNodeList(getFirst(alex), printPerson);
    printf("\n");
    
    printf("Foreach print\n");
    Person* p;
    linkedListForeach(p, alex){
        printf("%s \n", p->name);
    }
    printf("\n");
    
    /*
        Sort alphabetically using comparison function
        Alex <-> Bob <-> Charlie <-> David <-> Eric
    */
    printf("Sort:\n");
    sortNodes(alex, sortPersonsAlphabetically);
    printNodeList(alex, printPerson);
    printf("\n");
    
    /*
        Finding and removing a node while preserving order
    */
    printf("Finding and removing Charlie:\n");
    Node* target = findNode(alex, isCharlie);
    removeNodeFromList(target);
    printNodeList(alex, printPerson);
    printf("\n");
    
    return 0;
}

Person* newPerson(char name[256]){
    Person* person = malloc(sizeof(Person));
    strcpy(person->name, name);
    person->node.next = NULL; // Unavoidable technicality if using some compilers, otherwise unnecessary
    person->node.prev = NULL; // --||--
    return person;
}

void printPerson(Person* person){
    printf("%s\n", person->name);
}

int sortPersonsAlphabetically(Person* a, Person* b){
    return strcmp(a->name, b->name) > 0; //swap if b should be ahead of a
}

int isCharlie(Person* person){
    return !strcmp(person->name, "Charlie");
}



