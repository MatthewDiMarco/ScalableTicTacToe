/* ****************************************************************************
 * FILE:        user_input.c
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains functions for retrieving, modifying and returning/
 *              exporting all input from the user via the keyboard.
 *
 * LAST MOD:    22/09/19 
 * ***************************************************************************/
#include <stdio.h>

#include "user_input.h"

/* ****************************************************************************
 * NAME:        readInt
 * PURPOSE:     To get an integer between the specified lower and upper bounds
 *              via keyboard input.
 *              Can output a special message (msg).
 * IMPORTS:     msg (string), lower, upper (integers)
 * EXPORTS:     value (integer)
 * ***************************************************************************/
int readInt(char msg[], int lower, int upper)
{
    int value;
    do
    {
        printf("%s", msg);
        if(scanf("%d", &value) != 1)
        {
            /* input mismatch */
            printf("\ninput must be a whole number\n\n");

            /* eat up invalid chars */
            while(getchar() != '\n');        
   
            value = -1; /* stay in loop */
        }
        else
        {
            if((value < lower) || (value > upper)) 
            {
                printf("\ninput must be between %d and %d\n\n", lower, upper);
            }
        }
    }
    while((value < lower) || (value > upper));
    return value; 
}
