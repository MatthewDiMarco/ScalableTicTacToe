/* ****************************************************************************
 * FILE:        user_interface.c
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains functions for outputting the central menu and sub
 *              menus. Also contains functionality for displaying various 
 *              graphics to the terminal, such as the tic-tac-toe N*M board.
 *
 * LAST MOD:    28/09/19 
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user_interface.h"
#include "user_input.h"
#include "file_manager.h"
#include "board.h"
#include "linked_list.h" 

/* ****************************************************************************
 * NAME:        mainMenu
 *
 * PURPOSE:     To print a list of options to the terminal which the user can
 *              select from. The appropriate function will be called based
 *              on what the user selected.
 *
 * IMPORTS:     settingsFileName (string)
 * EXPORTS:     none
 * ***************************************************************************/
void mainMenu(char* settingsFileName)
{ 
    int option, m, n, k, ii, running;
    char* ops[] = { "1: Start new game\n", 
                    "2: View settings\n",
                    "3: View logs\n",
                    "4: Save logs\n",
                    "5: Exit\n" };

    /* validate settings file */
    if(readSettings(settingsFileName, &m, &n, &k) == -1)
    {
        printf("failed to read %s: shutting down...\n\n", settingsFileName);
    }
    else /* if settings are ok, enter main loop */
    {
        printf("\n  ---Welcome---\n");
        running = TRUE;
        do
        {
            /* print menu */
            printf("\nSelect an option\n----------------\n");
            for(ii = 0; ii < NUM_OPTIONS; ii++)
            {
                printf(ops[ii]);
            }

            /* get user input and execute option */
            option = readInt("--> ", 1, NUM_OPTIONS);
            switch(option)
            {
                case 1 :    
                    playGame(createBoard(m, n, k));
                    break;

                case 2 :
                    printf("\nSETTINGS:\n---------\n");
                    printf("   M=%d\n   N=%d\n   K=%d\n---------\n", m, n, k);
                    break;

                case 3 :
                    printf("\nfunction (3) not implemented yet\n");            
                    break;

                case 4 :
                    printf("\nfunction (4) not implemented yet\n");            
                    break;

                case 5 : 
                    printf("\ngoodbye...\n\n");
                    running = FALSE;            
                    break;

                default : 
                    /* can't get here */ 
                    break;
            }
        }
        while(running == TRUE);
    }
}

/*TODO: add comment; will probs return and import a linked list*/
void playGame(Board* board)
{  
    int err, xx, yy, option; 
    int playing = TRUE, player = 1;
    while(playing)
    {
        printf("\n");
        displayBoard(board);
        printf("\nPLAYER %d's TURN\n\n", player);
        /* sub menu */
        printf("1: Take turn\n2: Quit\n");
        option = readInt("--> ", 1, 2);
        switch(option)
        {
            case 1 :
                 do /* keep reading coords until valid */
                {
                    readCoords(&xx, &yy);
                    err = insertMove(board, player, xx, yy);
                } while(err == -1);
                printf("\nINSERTING INTO (%d,%d)\n", xx, yy);
                break;

            case 2 :
                playing = FALSE;
                break;
        }

        /* Swap player turn */
        if(player == 1)
        {
            player = 2;
        }
        else
        {
            player = 1;
        }
    } 
    printf("\nDRAW\n"); /*temp*/
    destroyBoard(board);
}

/* ****************************************************************************
 * NAME:        displayBoard
 *
 * PURPOSE:     To display the contents of a board to the terminal.
 *
 * IMPORTS:     board (Board pointer) 
 * EXPORTS:     none
 * ***************************************************************************/
void displayBoard(Board* board)
{
    int ii, jj;

    /* print upper border */
    printf("==");
    for(ii = 0; ii < board->width; ii++) 
    {
        printf("====");
    }
    printf("=\n");

    /** 
     * Print board. 
     * height is multiplied by 2 to include inner borders.
     */
    for(ii = 0; ii < board->height; ii++)
    {
        printf("||");
        for(jj = 0; jj < board->width; jj++)
        {
            if(board->map[ii][jj] == 0)
            {
                printf("   |");
            }
            else if(board->map[ii][jj] == 1)
            {
                printf(" X |");
            }
            else
            {
                printf(" O |");
            }
        }
        printf("|\n");
       
        /* if we're on the last iteration, we don't need an inner border */
        if(ii != board->height - 1)
        { 
            /* print inner border */
            printf("||");
            for(jj = 0; jj < board->width; jj++) 
            {
                /* if we're on the last iteration, close the row with '|' */
                if(jj == board->width - 1)
                {
                    printf("---|");
                } 
                else
                {
                    printf("----");
                }
            }
            printf("|\n");
        }
    }

    /* print lower border */
    printf("==");
    for(ii = 0; ii < board->width; ii++) 
    {
        printf("====");
    } 
    printf("=\n");
}
