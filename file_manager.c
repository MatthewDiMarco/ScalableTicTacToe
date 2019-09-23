/* ****************************************************************************
 * FILE:        file_manager.c
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains functionality for all file reading and writing, 
 *              including: 
 *               -> loading game settings
 *               -> saving logs
 *               -> reading logs
 *
 * LAST MOD:    22/09/19 
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_manager.h"
#include "linked_list.h"

/* ****************************************************************************
 * NAME:        readSettings
 * PURPOSE:     To print a list of options to the terminal which the user can
 *              select from. The appropriate function will be called based
 *              on what the user selected.
 * IMPORTS:     file (string), inM, inN, inK (integer pointers)
 * EXPORTS:     status (integer: -1 if error occured)
 * ***************************************************************************/
int readSettings(char* file, int* inM, int* inN, int* inK)
{
    int status = 0;
    return status;
}
