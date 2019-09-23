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

/**
 * Describes the length of a line in a valid settings file (including new
 * line). for instance: 'M=5' is 3 chars, + '\' & 'n' ... thus 5 chars needed.
 *
 * Describes number of available settings in a valid settings file.
 **/
#define LENGTH_OF_SETTINGS 5
#define NUM_SETTINGS 3

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
