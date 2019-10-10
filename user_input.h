/* ****************************************************************************
 * FILE:        user_input.h
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains definitions of prototypes and macros used inside
 *              of user_input.c
 *
 * LAST MOD:    22/09/19 
 * ***************************************************************************/

/* constants */
#define MAX_LINE_SIZE 20 /* no integers bigger than 20 digits */

/* typdefs, enums */

/* structs */

/* prototype declarations */

/* ****************************************************************************
 * NAME:        readInt
 * PURPOSE:     To get an integer between the specified lower and upper bounds
 *              via keyboard input.
 *              Can output a special message (msg)
 * IMPORTS:     msg (string), lower, upper (integers)
 * EXPORTS:     value (integer)
 * ***************************************************************************/
int readInt(char msg[], int lower, int upper);

/* ****************************************************************************
 * NAME:        readCoords
 *
 * PURPOSE:     To read in the x and y coordinates for a board via format <x,y>
 *              returns -1 if errors occur, 0 otherwise.
 *
 * IMPORTS:     xx, yy (integer pointers)
 * EXPORTS:     none
 * ***************************************************************************/
int readCoords(int* xx, int* yy);
