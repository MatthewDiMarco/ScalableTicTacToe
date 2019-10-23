/* ****************************************************************************
 * FILE:        file_manager.c
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Responsible for all file reading and writing, including saving
 *              of log files and reading of game settings.
 *
 * LAST MOD:    28/09/19 
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#include "file_manager.h"
#include "linked_list.h"
#include "board.h"
#include "user_interface.h"

/* static prototypes */
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

        /* Check that K is <= M & N (possible to win?) */
        if(((mFound == TRUE) && (nFound == TRUE) && (kFound == TRUE)) && 
           ((*inK > *inM) && (*inK > *inN)))
        {
            printf("K must be less than or equal to M, N or both\n");
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
 *              The name of the file will be of the format: 
 *
 *                  MNK_m-n-k_hour-min_day-month.log
 *
 *              <time.h> is used to capture the system's current time.
 *
 *              Acknowledgements: techiedelight.com for the tutorial on 
 *              accessing system time/date.
 *              Ref: https://www.techiedelight.com/print-current-date-and-time-in-c/
 *
 * IMPORTS:     sessionList (LinkedList), settings(m-n-k) (integers)
 * EXPORTS:     status (integer: -1 if error occured)
 * ***************************************************************************/
int saveLogs(LinkedList* sessionList, int m, int n, int k)
{
    int status = 0, gameNum;
    LinkedList* game;
    Log* log;
    FILE* outfile;
    char flname[30];

    /*Generate file name*/
    time_t now;
    struct tm* local;

    /*Get curr time*/
    time(&now);
    local = localtime(&now);     

    /*Write to string*/
    sprintf(flname, "MNK_%d-%d-%d_%d-%d_%d-%d.log",     /*+1 month to compensate for 0-based indexing*/
    m, n, k, local->tm_hour, local->tm_min, local->tm_mday, local->tm_mon + 1);

    /*Create file*/
    outfile = fopen(flname, "w");
    if(outfile == NULL)
    {
        perror("There was an error creating the save file");
        status = -1;        
    }
    else /*Begin writing*/
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
 *
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
