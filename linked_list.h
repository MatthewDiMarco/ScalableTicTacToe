/* ****************************************************************************
 * FILE:        linked_list.h
 * CREATED:     27/09/19
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Header file for generic linked list.
 *              Contains structs for a list node and the list itself, as well
 *              as all function declarations.
 *
 * LAST MOD:    29/09/19
 * MOD BY:      Matthew Di Marco
 * ***************************************************************************/

/** 
 * Structs and Typedefs 
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* function pointer for freeing and printing */
typedef void (*DATA_FUNC)(void* data);

/* a list node */
typedef struct LinkedListNode 
{
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

/* the list itself */
typedef struct 
{
    int size;
    LinkedListNode* head;
    LinkedListNode* tail;
} LinkedList;

#endif

/** 
 * Prototypes 
 */

/* ****************************************************************************
 * NAME:        createLinkedList
 * 
 * PURPOSE:     To generate a blank linked list.
 *
 * IMPORT:      none
 * EXPORT:      pointer to a linked list.
 * ***************************************************************************/
LinkedList* createLinkedList();

/* ****************************************************************************
 * NAME:        insertStart
 * 
 * PURPOSE:     To insert a new element at the head of the list.
 * 
 * IMPORT:      list (pointer to a linked list), 
 *              value (generic pointer)
 * EXPORT:      none
 * ***************************************************************************/
void insertStart(LinkedList* list, void* value);

/* ****************************************************************************
 * NAME:        removeStart
 * 
 * PURPOSE:     To remove and free the frontmost element in the list.
 *              If the list is empty, NULL is returned as the data.
 *              Note: the returned data may (should) be malloced, so 
 *              it must be free'd after return.
 * 
 * IMPORT:      list (pointer to a linked list)
 * EXPORT:      value (generic pointer)
 * ***************************************************************************/
void* removeStart(LinkedList* list);

/* ****************************************************************************
 * NAME:        insertLast
 * 
 * PURPOSE:     To insert a new element at the tail of the list.
 * 
 * IMPORT:      list (pointer to a linked list), 
 *              value (generic pointer)
 * EXPORT:      none
 * ***************************************************************************/
void insertLast(LinkedList* list, void* value);

/* ****************************************************************************
 * NAME:        removeLast
 * 
 * PURPOSE:     To remove and free the tailmost element in the list.
 *              If the list is empty, NULL is returned as the data.
 *              Note: the returned data may (should) be malloced, so 
 *              it must be free'd after return.
 * 
 * IMPORT:      list (pointer to a linked list)
 * EXPORT:      value (generic pointer)
 * ***************************************************************************/
void* removeLast(LinkedList* list);

/* ****************************************************************************
 * NAME:        printLinkedList
 * 
 * PURPOSE:     To print the contents of the list to the terminal in descending
 *              order (i.e. from head to tail).
 * 
 * IMPORT:      list (pointer to a linked list), 
 *              printFunction (pointer to function for printing this data)
 * EXPORT:      none
 * ***************************************************************************/
void printLinkedList(LinkedList* list, DATA_FUNC printFunction);

/* ****************************************************************************
 * NAME:        freeLinkedList
 * 
 * PURPOSE:     To free all nodes and their corresponding data from heap
 *              memory, in addition the list itself.
 *              If any nodes were removed via removeStart/Last, then the 
 *              data returned from those functions must be free'd manually.
 * 
 * IMPORT:      list (pointer to a linked list),
 *              freeFunction (pointer to function for freeing this data)
 * EXPORT:      none
 * ***************************************************************************/
void freeLinkedList(LinkedList* list, DATA_FUNC freeFunction);
