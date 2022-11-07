#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<double_linked_list.h>


struct LinkedList *createList() {
    struct LinkedList *list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void destroyList(struct LinkedList **list) {
    struct LinkedList *listPointer = *list; 
    struct Node *currentNode = listPointer->tail;

    if (currentNode == NULL) {
        free(listPointer);
        *list = NULL;
        return;
    }
    if (currentNode == listPointer->head) {
        free(currentNode);
        free(listPointer);
        *list = NULL;
        return;
    }

    struct Node *previousNode = currentNode->previous;

    while (previousNode != NULL) {
        free(currentNode);
        currentNode = previousNode;
        previousNode = currentNode->previous;
    }
    
    free(currentNode);
    free(listPointer);
    *list = NULL;
}

struct Node *getNodeByIndex (struct LinkedList *list, int index) {
    struct Node *currentNode = list->head;
    if (currentNode == NULL) {
        printf("Index is out of bounds.");        
        return NULL;
    }
    for (int i = 0; i < index; i++) {
        if (currentNode->next != NULL) {
            currentNode = currentNode->next;
        } else {
            printf("Index is out of bounds.");        
            return NULL;
        }        
    }
    return currentNode;
}

struct Node *getNodeByStringValue (struct LinkedList *list, char *stringValue) {
    struct Node *currentNode = list->head;
    while (currentNode != NULL && strcmp(stringValue, currentNode->stringValue) != 0) { 
       currentNode = currentNode->next; 
    }
    return currentNode;
}

void addElement(struct LinkedList *list, char *stringValue) {
    if(list->head == NULL) {
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->previous = NULL;
        newNode->next = NULL;
        newNode->stringValue = stringValue;
        
        list->head = newNode;
        list->tail = newNode; 
        return;
    }    

    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->stringValue = stringValue;
    newNode->previous = list->tail;
    list->tail->next = newNode;
}

int insertElement(struct LinkedList *list, char *stringValue, int index) {
    struct Node *nodeToInsert = (struct Node*)malloc(sizeof(struct Node)); 
    nodeToInsert->stringValue = stringValue;
    struct Node *nodeToMove = getNodeByIndex(list, index);
    
    
    if (nodeToMove == NULL && index != 0) {
        printf("cant find element with index:%i\n", index);
        return 1; 
    } 

    if (nodeToMove == list->head && nodeToMove == list->tail) {
        list->head = nodeToInsert;
        nodeToInsert->next = nodeToMove;
        nodeToInsert->previous = NULL;
        nodeToMove->previous = nodeToInsert;
        return 0;
    } 
    if (nodeToMove == list->head) {
        list->head = nodeToInsert;
        nodeToInsert->next = nodeToMove;
        nodeToInsert->previous = NULL;
        nodeToMove->previous = nodeToInsert;
        return 0;
    }

    nodeToInsert->next = nodeToMove;
    nodeToInsert->previous = nodeToMove->previous;
    nodeToMove->previous->next = nodeToInsert;
    nodeToMove->previous = nodeToInsert;
     
    return 0;
}

char *getElement(struct LinkedList *list, int index) {
    struct Node *currentNode = getNodeByIndex(list, index);
    if (currentNode == NULL) {
        return NULL; 
    }
    return currentNode->stringValue;
}

int removeElement(struct LinkedList *list, char *stringValue) {
    struct Node *nodeToRemove = getNodeByStringValue(list, stringValue);

    if (nodeToRemove == NULL) {
        printf("cant find element with stringValue:%s\n", stringValue);
        return 1; 
    } 
    if (nodeToRemove == list->head && nodeToRemove == list->tail) {
        list->head = NULL;
        list->tail = NULL;
        free(nodeToRemove);
        return 0;
    } 
    if (nodeToRemove == list->head) {
        list->head = nodeToRemove->next;
        nodeToRemove->next->previous = NULL;
        free(nodeToRemove);
        return 0;
    }
    if (nodeToRemove == list->tail) {
        list->tail = nodeToRemove->previous;
        nodeToRemove->previous->next = NULL;
        free(nodeToRemove);
        return 0;
    }

    nodeToRemove->previous->next = nodeToRemove->next;
    nodeToRemove->next->previous = nodeToRemove->previous;
    free(nodeToRemove);
    return 0;
}

void printList(struct LinkedList *list) {
    struct Node *currentNode = list->head;
    while (currentNode != NULL) {
        printf("%s\n", currentNode->stringValue);
        currentNode = currentNode->next;
    }
}

