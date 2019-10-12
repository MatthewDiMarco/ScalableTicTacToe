/* ****************************************************************************
 * FILE:        user_input.c
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains functions for retrieving, modifying and returning/
 *              exporting all input from the user via the keyboard.
 *
 * LAST MOD:    23/09/19 
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user_input.h"
#include "board.h"

/* ****************************************************************************
 * NAME:        readInt
 *
 * PURPOSE:     To get an integer between the specified lower and upper bounds
 *              via keyboard input.
 *              Can output a prompt (msg).
 *
 * IMPORTS:     msg (string), lower, upper (integers)
 * EXPORTS:     value (integer)
 * ***************************************************************************/
int readInt(char msg[], int lower, int upper)
{
    char garbage[MAX_LINE_SIZE], input[MAX_LINE_SIZE]; 
    int value = lower - 1;

    /* prompt and get user input for analyzing */
    printf("%s", msg);
    fgets(input, sizeof(input), stdin); 
    if(sscanf(input, "%d%[^\n]", &value, garbage) != 1)
    {
        /* If we got here, the user entered excess (invalid) chars */
        printf("\ninput must be a whole number\n");
        value = lower - 1; /* return invalid value */
    }
    else
    {
        /* Here if the user's input is valid, but out of range */
        if((value < lower) || (value > upper)) 
        {
            printf("\ninput must be between %d and %d\n", lower, upper);
            value = lower - 1;
        }
    }

    return value;
}

/* ****************************************************************************
 * NAME:        readCoords
 *
 * PURPOSE:     To read in the x and y coordinates for a board via format <x,y>
 *              returns -1 if errors occur, 0 otherwise.
 *
 * IMPORTS:     xx, yy (integer pointers)
 * EXPORTS:     none
 * ***************************************************************************/
int readCoords(int* xx, int* yy)
{
    int status = 0;    

    /*coord can be upto 8 char long ( e.g. "<xxx>,<yyy>\0" )*/
    char garbage[MAX_LINE_SIZE], input[MAX_LINE_SIZE];
 
    printf("\nEnter tile coordinates with format \"x,y\"\n--> ");   
    fgets(input, sizeof(input), stdin); 
    if(sscanf(input, "%d,%d%[^\n]", xx, yy, garbage) != 2)
    {
        printf("\nBad format. Try something like --> 2,3\n");
        status = -1;
    }

    return status;   
}

/* ****************************************************************************
 * NAME:        readMNK
 *
 * PURPOSE:     To read and validate the MNK game settings from the terminal
 *              via keyboard input. (Only used in editor mode)
 *
 * IMPORTS:     inM, inN, inK (integer pointers)
 * EXPORTS:     none
 * ***************************************************************************/
void readMNK(int* inM, int* inN, int* inK)
{
    int status = 0;
    char garbage[MAX_LINE_SIZE], input[MAX_LINE_SIZE];

    do
    {
        printf("\nEnter game settings with format \"m,n,k\"\n--> ");   
        fgets(input, sizeof(input), stdin); 
        if(sscanf(input, "%d,%d,%d%[^\n]", inM, inN, inK, garbage) != 3)
        {
            printf("\nBad format. Try something like --> 4,5,3\n");
            status = -1;
        }

        /* validate the settings */
        else if(((*inM < LOWER) || (*inM > UPPER)) ||
                ((*inN < LOWER) || (*inN > UPPER)) ||
                ((*inK < LOWER) || ((*inK > *inM) && (*inK > *inN))))
        {
            printf("\nOne or more settings out of range.\n");
            printf("Values should be between %d and %d.\n", LOWER, UPPER);
            printf("K should be no greater than both M and N.\n");
            status = -1; 
        }
        else
        {       
            status = 0;
        } 
    }
    while(status == -1); 
}
