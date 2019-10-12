/* ****************************************************************************
 * FILE:        LinkedListTest.c
 * CREATED:     Friday, 6th September 2019 11:40:35 am
 * AUTHOR:      Jonathon Winter
 * 
 * PURPOSE:     Test harness for linked_list.c (generic).
 *
 * LAST MOD:    Friday, 11th October 2019 17:07:00 pm
 * MOD BY:      Matthew Di Marco
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

/* declarations */
void printString(void* str);
void freeString(void* str);

int main(int argc, char const *argv[])
{
    int ii;
    LinkedList* list = NULL;
    char* data;
    char* strings[4] = { "abc\n",
                         "def\n",
                         "ghi\n",
                         "jkl\n" };
    char* input[4];
    for(ii = 0; ii < 4; ii++)
    {
        input[ii] = (char*)malloc(sizeof(char) * (strlen(strings[ii]) + 1));
        strcpy(input[ii], strings[ii]);
    } 

    /* CREATING */

    printf("Creating List: ");
    list = createLinkedList();
    if(list == NULL || list->head != NULL)
    {
       printf("FAILED\n");
    }
    else
    {
       printf("PASSED\n");
    }

    /* INSERTING FIRST */

    /* (1) insert into empty list */
    printf("Inserting First: ");
    insertStart(list, input[0]);
    if(list->head == NULL || list->tail == NULL)
    {
       printf("FAILED\n");
    }
    else if(strcmp(list->head->data, input[0]) == 0)
    {
       printf("PASSED\n");
    }
    else
    {
       printf("FAILED\n");
    }

    /* (2) insert into NOT empty list */
    printf("Inserting First (2): ");
    insertStart(list, input[1]);
    if(list->head == NULL || list->tail == NULL)
    {
       printf("FAILED\n");
    }
    else if(strcmp(list->head->data, input[1])==0 && 
            strcmp(list->tail->data, input[0])==0)
    {
       printf("PASSED\n");
    }
    else
    {
       printf("FAILED\n");
    }

    /*REMOVING FIRST*/

    /* (1) removing from list with 2 elements */
    printf("Remove First: ");
    data = removeStart(list);
    if(strcmp(data, input[1]) == 0)
    {
       printf("PASSED\n");
    }
    else
    {
       printf("FAILED\n");
    }

    /* (2) removing from list with a single element */
    printf("Remove First (2): ");
    data = removeStart(list);
    if(strcmp(data, input[0]) == 0)
    {
       printf("PASSED\n");
    }
    else
    {
       printf("FAILED\n");
    }

    /* (3) trying to remove from empty list */
    printf("Remove First (3): ");
    data = removeStart(list);
    if(data == NULL)
    {
       printf("PASSED\n");
    }
    else
    {
       printf("FAILED\n");
    }

    /** 
     * normally would free data here, but all data is being re-inserted at the 
     * end (to test the free function), so no need. 
     */

    /*INSERTING LAST*/

    /* (1) insert into empty list */
    printf("Inserting Last: ");
    insertLast(list, input[2]);
    if(list->head == NULL || list->tail == NULL)
    {
       printf("FAILED\n");
    }
    else if(strcmp(list->head->data, input[2]) == 0)
    {
       printf("PASSED\n");
    }
    else
    {
       printf("FAILED\n");
    }

    /* (2) insert into NOT empty list */
    printf("Inserting Last (2): ");
    insertLast(list, input[3]);
    if(list->head == NULL || list->tail == NULL)
    {
       printf("FAILED\n");
    }
    else if(strcmp(list->head->data, input[2])==0 && 
            strcmp(list->tail->data, input[3])==0)
    {
       printf("PASSED\n");
    }
    else
    {
       printf("FAILED\n");
    }

    /*REMOVING LAST*/

    /* (1) removing from list with 2 elements */
    printf("Remove Last: ");
    data = removeLast(list);
    if(strcmp(data, input[3]) == 0)
    {
       printf("PASSED\n");
    }
    else
    {
       printf("FAILED\n");
    }

    /* (2) removing from list with a single element */
    printf("Remove Last (2): ");
    data = removeLast(list);
    if(strcmp(data, input[2]) == 0)
    {
       printf("PASSED\n");
    }
    else
    {
       printf("FAILED\n");
    }

    /* (3) trying to remove from empty list */
    printf("Remove Last (3): ");
    data = removeLast(list);
    if(data == NULL)
    {
       printf("PASSED\n");
    }
    else
    {
       printf("FAILED\n");
    }

    /*FREEING*/

    insertLast(list, input[0]);
    insertLast(list, input[1]);
    insertLast(list, input[2]);
    insertLast(list, input[3]);
    printf("Free Linked List: ");
    freeLinkedList(list, &freeString);
    printf("PASSED\n");   
 
    return 0;
}

/* example function for printing */
void printString(void* str)
{
    char* print = (char*)(str); /* cast */
    printf("%s", print);
}

/* example function for freeing */
void freeString(void* str)
{
    free((char*)str);
}
