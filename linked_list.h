/* ****************************************************************************
 * FILE:        linked_list.h
 * CREATED:     27/09/19
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Header file for generic linked list.
 *
 * LAST MOD:    12/10/19
 * MOD BY:      Matthew Di Marco
 * ***************************************************************************/

/** 
 * Structs and typedefs 
 */

#ifndef LL
#define LL

/** 
 * Function pointer for handling generic list data (i.e. freeing and printing)
 */
typedef void (*DATA_FUNC)(void* data);

/** 
 * A node in the list.
 * Contains a pointer to a value and a reference to the next node.
 */
typedef struct LinkedListNode 
{
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

/**
 * The list itself.
 * Contains references to the beginning and end of list.
 */
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
 *              Returns the data, which must be free'd later.
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
 *              Returns the data, which must be free'd later.
 * 
 * IMPORT:      list (pointer to a linked list)
 * EXPORT:      none
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
