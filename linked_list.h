/**
 * FILE:        linked_list.h
 * CREATED:     27/09/19
 * AUTHOR:      Matthew Di Marco
 * -----
 * LAST MOD:    27/09/19
 * MOD BY:      Matthew Di Marco
 * ----- 
 * PURPOSE:     Header file for generic linked list.
 *              Contains structs for a list node and the list itself, as well
 *              as all function declarations.
 */

/* structs and typedefs */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* function pointer for freeing and printing */
typedef void (*DATA_FUNC)(void* data);

/* a list node */
typedef struct LinkedListNode {
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

/* the list itself */
typedef struct {
    int size;
    LinkedListNode* head;
    LinkedListNode* tail;
} LinkedList;
#endif

/* prototypes */

LinkedList* createLinkedList();

void insertStart(LinkedList* list, void* value);

void* removeStart(LinkedList* list);

void insertLast(LinkedList* list, void* value);

void* removeLast(LinkedList* list);

void printLinkedList(LinkedList* list, DATA_FUNC printFunction);

void freeLinkedList(LinkedList* list, DATA_FUNC freeFunction);
