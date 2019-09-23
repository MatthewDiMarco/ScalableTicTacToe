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
