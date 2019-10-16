/* ****************************************************************************
 * FILE:        user_input.h
 * CREATED:     29/08/19
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Header file for user_input.c
 *
 * LAST MOD:    12/10/19
 * MOD BY:      Matthew Di Marco 
 * ***************************************************************************/

/**
 * Constants
 */

/* Size of lines when reading/parsing user input */
#define MAX_LINE_SIZE 30

/**
 * Prototype declarations 
 */

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

/* ****************************************************************************
 * NAME:        readMNK
 *
 * PURPOSE:     To read and validate the MNK game settings from the terminal
 *              via keyboard input. (Only used in editor mode)
 *
 * IMPORTS:     inM, inN, inK (integer pointers)
 * EXPORTS:     none
 * ***************************************************************************/
void readMNK(int* inM, int* inN, int* inK);
