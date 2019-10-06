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
    do
    {
        /* prompt and get user input for analyzing */
        printf("%s", msg);
        fgets(input, sizeof(input), stdin); 
        if(sscanf(input, "%d%[^\n]", &value, garbage) != 1)
        {
            /* If we got here, the user entered excess (invalid) chars */
            printf("\ninput must be a whole number\n\n");
            value = lower - 1; /* stay in loop */
        }
        else
        {
            /* Here of the user's input is valid, but out of range */
            if((value < lower) || (value > upper)) 
            {
                printf("\ninput must be between %d and %d\n\n", lower, upper);
            }
        }
    }
    while((value < lower) || (value > upper));

    return value;
}

/* ****************************************************************************
 * NAME:        readCoords
 *
 * PURPOSE:     To read in the x and y coordinates for a board.
 *
 * IMPORTS:     xx, yy (integer pointers)
 * EXPORTS:     none
 * ***************************************************************************/
void readCoords(int* xx, int* yy)
{
    int ix, iy;
    printf("\nSelect a tile (x,y)\n");   
    ix = readInt("x -> ", 0, 9);
    iy = readInt("y -> ", 0, 9);
    *xx = ix;
    *yy = iy;
}
