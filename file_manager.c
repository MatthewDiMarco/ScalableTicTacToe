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
 * LAST MOD:    23/09/19 
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_manager.h"
#include "linked_list.h"

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
int readSettings(char* file, int* inM, int* inN, int* inK)
{
    int status = 0, ii;
    char lines[NUM_SETTINGS][LENGTH_OF_SETTINGS];

    /* open and check file before reading*/
    FILE* settings = fopen(file, "r");
    if(file == NULL)
    {
        perror("there was an error opening the file");
        status = -1;
    } 
    else 
    {
        /* loop 3 times, storing each line of the file in a local array */
        for(ii = 0; ii < NUM_SETTINGS; ii++)
        {
            fgets(lines[ii], LENGTH_OF_SETTINGS, settings);
        }

        /* check format of lines. exactly 1 item should have been read */  
        if(sscanf(lines[0], "M=%d", inM) != 1 ||
           sscanf(lines[1], "N=%d", inN) != 1 ||
           sscanf(lines[2], "K=%d", inK) != 1)
        {
            printf("\nbad format - please check settings file.\n");
            printf("file should resemble:\n  M=x\n  N=y\n  K=z\n\n");
            status = -1;
        }

        /* final error checking */
        if(ferror(settings))
        {
            perror("error closing input file");
            status = -1;
        }
        fclose(settings);
    }
    return status;
}
