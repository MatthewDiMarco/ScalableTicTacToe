/* ****************************************************************************
 * FILE:        file_manager.h
 * CREATED:     29/08/19
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Header file for file_manager.c
 *
 * LAST MOD:    12/10/19
 * MOD BY:      Matthew Di Marco
 * ***************************************************************************/
#include "linked_list.h"

/**
 * Constants
 */

/* Describes the length of a line in a settings file (upto 3 digits) */
#define LENGTH_OF_SETTINGS 8

/* These constants can be used with integers to model booleans. */
#define FALSE 0
#define TRUE !FALSE

/**
 * Prototype declarations
 */

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

/* ****************************************************************************
 * NAME:        saveLogs
 *
 * PURPOSE:     Save all the game logs to a txt file for a given session.
 *
 * IMPORTS:     sessionList (LinkedList)
 * EXPORTS:     status (integer: -1 if error occured)
 * ***************************************************************************/
int saveLogs(LinkedList* sessionList, int m, int n, int k);
