/* ****************************************************************************
 * FILE:        linked_list.c
 * CREATED:     27/09/19
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 * 
 * PURPOSE:     A linked list structure for dynamically storing generic data
 *              in a series of nodes using void pointers.
 *
 * LAST MOD:    29/09/19
 * MOD BY:      Matthew Di Marco
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

/* ****************************************************************************
 * NAME:        createLinkedList
 * 
 * PURPOSE:     To generate a blank linked list.
 *
 * IMPORT:      none
 * EXPORT:      pointer to a linked list.
 * ***************************************************************************/
LinkedList* createLinkedList()
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    
    /* init */
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    
    return list;
}

/* ****************************************************************************
 * NAME:        insertStart
 * 
 * PURPOSE:     To insert a new element at the head of the list.
 * 
 * IMPORT:      list (pointer to a linked list), 
 *              value (generic pointer)
 * EXPORT:      none
 * ***************************************************************************/
void insertStart(LinkedList* list, void* value)
{
    /* initialize the new node */ 
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));  
    newNode->data = value;    
    newNode->next = NULL;

    if(list->size < 1) /* empty */
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        /* make newNode point to head node, and head point to newNode */
        newNode->next = list->head;
        list->head = newNode;
    }

    list->size++;
}

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
void* removeStart(LinkedList* list)
{
    LinkedListNode* temp;
    void* value;

    if(list->size < 1) /* empty */
    {
        value = NULL;
    }
    else
    {
        temp = list->head; /* save old head */
        value = list->head->data; /* data to be returned */
        list->head = list->head->next; /* update to new head */

        /* if that was the last element, head AND tail should point to null */
        if(list->head == NULL)
        {
            list->tail = NULL;
        }

        /* delete (free) old head */
        free(temp); 
   
        list->size--;
    }

    return value; 
}

/* ****************************************************************************
 * NAME:        insertLast
 * 
 * PURPOSE:     To insert a new element at the tail of the list.
 * 
 * IMPORT:      list (pointer to a linked list), 
 *              value (generic pointer)
 * EXPORT:      none
 * ***************************************************************************/
void insertLast(LinkedList* list, void* value)
{
    /* initialize the new node */ 
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->data = value;
    newNode->next = NULL; 

    if(list->size < 1) /* empty */
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        /* insert node and update tail */ 
        list->tail->next = newNode;
        list->tail = newNode; 
    }

    list->size++;
}

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
void* removeLast(LinkedList* list)
{
    LinkedListNode *node, *prevNode;
    void* value;

    if(list->size < 1) /* empty */
    {
         value = NULL;
    }
    else
    {
        /* find last and second-last element */
        prevNode = NULL;
        node = list->head;
        while(node->next != NULL)
        {
            prevNode = node;
            node = node->next; 
        }
        value = node->data; /* data to be returned */
        
        /* delete (free) the node */
        free(node); 

        /* update pointers */
        if(prevNode != NULL) /* if list NOT empty */
        {
            prevNode->next = NULL;
            list->tail = prevNode;
        }
        else /* just deleted last node; list is now empty */        
        {
            list->head = NULL;
            list->tail = NULL;
        }

        list->size--;
    }

    return value;
}

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
void printLinkedList(LinkedList* list, DATA_FUNC printFunction)
{
    LinkedListNode *node;
    if((list->head) == NULL)
    {
        printf("\nlist is empty\n\n");
    }
    else
    {
        node = list->head;
        while(node != NULL)
        {   
            (*printFunction)(node->data);     
            node = node->next;
        }
    }
}

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
void freeLinkedList(LinkedList* list, DATA_FUNC freeFunction)
{
    LinkedListNode *node, *nextNode;
    node = list->head;
    while(node != NULL)
    {
        nextNode = node->next;

        (*freeFunction)(node->data);
        free(node);        

        node = nextNode;
    }
    free(list);
    list = NULL;
}
