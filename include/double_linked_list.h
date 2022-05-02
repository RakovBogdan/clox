#ifndef DOUBLE_LINKED_LIST_H_INCLUDED
#define DOUBLE_LINKED_LIST_H_INCLUDED


struct Node {
    struct Node *previous;
    struct Node *next;
    char *stringValue;
};

struct LinkedList {
    struct Node *head;
    struct Node *tail;
};

struct LinkedList *createList();
void destroyList(struct LinkedList **list);

void addElement(struct LinkedList *list, char *stringValue); 
int insertElement(struct LinkedList *list, char* stringValue, int index);
char *getElement(struct LinkedList *list, int index);
int removeElement(struct LinkedList *list, char *stringValue);
void printList(struct LinkedList *list);

#endif

