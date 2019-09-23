/* ****************************************************************************
 * FILE:        file_manager.h
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains definitions of prototypes and macros used inside
 *              of file_manager.h
 *
 * LAST MOD:    22/09/19 
 * ***************************************************************************/

/* constants */

/* typdefs, enums */

/* structs */

/* prototype declarations*/

/* ****************************************************************************
 * NAME:        readSettings
 * PURPOSE:     To print a list of options to the terminal which the user can
 *              select from. The appropriate function will be called based
 *              on what the user selected.
 * IMPORTS:     file (string), inM, inN, inK (integer pointers)
 * EXPORTS:     status (integer: -1 if error occured)
 * ***************************************************************************/
int readSettings(char* file, int* inM, int* inN, int* inK);
