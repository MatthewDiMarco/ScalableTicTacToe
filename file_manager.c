/* ****************************************************************************
 * FILE:        file_manager.c
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains functionality for all file reading and writing, 
 *              including: 
 *               -> loading game settings
 *               -> saving logs
 *
 * LAST MOD:    28/09/19 
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "file_manager.h"
#include "linked_list.h"
#include "board.h"

/* static function declarations */
static int processLine(char* line, int* dupe, int* value, int lineNum);

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
    int status = 0, numLines, 
    mFound = FALSE, nFound = FALSE, kFound = FALSE;
    char line[LENGTH_OF_SETTINGS];

    /* Open and check file before reading*/
    FILE* settings = fopen(file, "r");
    if(settings == NULL)
    {
        perror("there was an error opening the file");
        status = -1;
    } 
    else 
    {
        /* Loop through each first 3 lines of the file checking for errors */
        numLines = 0;
        while((fgets(line, LENGTH_OF_SETTINGS, settings) != NULL))
        {
            numLines++;

            /** 
             * Check if this line equals either of the formats, ignoring the
             * associated value and case sensitivity. Error if neither. 
             */ 
            if(strncasecmp(line, "M=", 2) == 0)
            {
                if(processLine(line, &mFound, inM, numLines) == -1)
                {
                    status = -1;
                }
            }
            else if(strncasecmp(line, "N=", 2) == 0)
            {
                if(processLine(line, &nFound, inN, numLines) == -1)
                {
                    status = -1;
                }
            }
            else if(strncasecmp(line, "K=", 2) == 0)
            {
                if(processLine(line, &kFound, inK, numLines) == -1)
                {
                    status = -1;
                }
            }
            else /* bad format */
            {
                printf("line %d has invalid format\n", numLines);
                status = -1;
            }
        } 

        /* Miss any settings? */
        if(mFound == FALSE)
        {   
            printf("missing setting 'M'\n");
            status = -1;
        }
        if(nFound == FALSE)
        {   
            printf("missing setting 'N'\n");
            status = -1;
        }
        if(kFound == FALSE)
        {   
            printf("missing setting 'K'\n");
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

/* ****************************************************************************
 * NAME:        saveLogs
 *
 * PURPOSE:     Save all the game logs to a txt file for a given session.
 *
 * IMPORTS:     sessionList (LinkedList)
 * EXPORTS:     status (integer: -1 if error occured)
 * ***************************************************************************/
int saveLogs(LinkedList* sessionList, int m, int n, int k)
{
    int status = 0, gameNum;
    LinkedList* game;
    Log* log;
    FILE* outfile;
    outfile = fopen("TEMP_SAVE_NAME", "w");
    if(outfile == NULL)
    {
        perror("There was an error creating the save file");
        status = -1;        
    }
    else
    {
        /*Print settings*/
        fprintf(outfile, "SETTINGS:\n   M=%d\n   N=%d\n   K=%d\n\n", m, n, k);    

        /*Print games*/
        gameNum = 0;
        game = (LinkedList*)removeStart(sessionList);
        while(game != NULL) /*Loop through the games*/
        {
            gameNum++;
            fprintf(outfile, "GAME %d\n", gameNum);
            log = (Log*)removeStart(game);
            while(log != NULL) /*Loop through the logs in a given game*/
            {
                fprintf(outfile, "   Turn: %d\n   Player: %c\n   Location: %s\n", 
                        log->turn, log->player, log->location);
                free(log); /*don't need it anymore*/
                log = (Log*)removeStart(game);
                fprintf(outfile, "\n");
            }
            freeLinkedList(game, &freeLog); /*data inside is already free*/
            game = (LinkedList*)removeStart(sessionList);
        }
        sessionList = NULL;

        /* Final error checking */
        if(ferror(outfile))
        {
            perror("There was an error closing the save file");
            status = -1;
        }
        fclose(outfile);
    }
    return status;
}

/* ****************************************************************************
 * NAME:        processLine
 *
 * PURPOSE:     Helper for the readSettings() function.
 *              Takes a line and checks that:
 *                  -> this settings has not already been read (duplicate)
 *                  -> the associated value is a positive integer between the
 *                     appropriate bounds.
 *              Should an error occur, a message will be printed and the
 *              function will return -1 to indicate a failure.
 *
 * IMPORTS:     line (string), dupe (boolean pointer), value (integer pointer),
 *              lineNum (the line we're on)
 * EXPORTS:     status (integer: -1 if error occured)
 * ***************************************************************************/
static int processLine(char* line, int* dupe, int* value, int lineNum)
{
    int status = 0;
    if(*dupe == FALSE) /* Check for duplicate */
    {
        /** 
         * Use sscanf to scan the string line for the following: 
         *    %*[^=] : collect all characters until we hit '=', then
         *             ignore them with the '*' char.
         *    %d : The value we wish to validate.
         */
        sscanf(line, "%*[^=]=%d", value);
        if(*value < LOWER || *value > UPPER)
        {
            printf("value must be between %d and %d at line %d\n", 
                    LOWER, UPPER, lineNum);
            status = -1;
        } 
        *dupe = TRUE;
    }
    else /* This is a duplicate setting */
    {
        printf("duplicate setting at line %d\n", lineNum);
        status = -1;
    }

    return status;
}
