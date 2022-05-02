#include<stdio.h>
#include<double_linked_list.h>

int main() {
    printf("Hello, world!\n");
    struct LinkedList *list = createList();
    addElement(list, "third element");
    insertElement(list, "second element", 0);
    insertElement(list, "first element", 0);
    printList(list);
    printf("\n");
    char *secondElement = getElement(list, 1);
    printf("the second element is: %s\n", secondElement);
    
    removeElement(list, "third element");
    insertElement(list, "Between first and second", 1);
    printList(list);
    destroyList(&list);
    return 0;
}
