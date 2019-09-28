/* ****************************************************************************
 * FILE:        file_manager.h
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains definitions of prototypes and macros used inside
 *              of file_manager.h
 *
 * LAST MOD:    23/09/19 
 * ***************************************************************************/

/* macros and constants */

/**
 * Describes the length of a line in a valid settings file (including new
 * line character).
 */
#define LENGTH_OF_SETTINGS 6

/**
 * These constants can be used with integers to model booleans.
 * (Ref: Lecture 2: Environments - slide 15)
 */
#define FALSE 0
#define TRUE !FALSE

/* typdefs, enums */

/* structs */

/* prototype declarations*/

/* ****************************************************************************
 * NAME:        readSettings
 *
 * PURPOSE:     To read in the 3 game settings (M, N and K) from a txt file.
 *              Should an error occur (e.g. bad format, empty file, etc), -1 
 *              will be returned.
 *              otherwise, 0 will be returned.
 *
 * IMPORTS:     file (string), inM, inN, inK (integer pointers)
 * EXPORTS:     status (integer: -1 if error occured)
 * ***************************************************************************/
int readSettings(char* file, int* inM, int* inN, int* inK);
