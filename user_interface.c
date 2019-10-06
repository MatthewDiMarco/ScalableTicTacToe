/* ****************************************************************************
 * FILE:        user_interface.c
 * CREATED:     29/08/19
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains functions for outputting the central menu and sub
 *              menus. Also contains functionality for displaying various 
 *              graphics to the terminal, such as the tic-tac-toe N*M board.
 *
 * LAST MOD:    28/09/19
 * MOD BY:      Matthew Di Marco 
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
    LinkedList *games = NULL, *log = NULL;
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
        games = createLinkedList();
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
                case 1 : /* Start new game */  
                    log = createLinkedList(); 
                    playGame(createBoard(m, n, k), log);
        
                    /** 
                     * Add the previous game's logs to the list of log lists.
                     * Set the log to null so it's ready for another game, and 
                     * do NOT free the log (we want to keep it for displaying/
                     * saving). All game logs will be free'd when we destroy
                     * 'games' at the end of runtime.
                     */
                    if(log->size > 0) /* were any moves made? */
                    {
                        insertLast(games, log); 
                    }
                    log = NULL;
                    break;

                case 2 : /* View settings */
                    printf("\nSETTINGS:\n---------\n");
                    printf("   M=%d\n   N=%d\n   K=%d\n---------\n", m, n, k);
                    break;

                case 3 : /* View logs */
                    if(games->size < 1)
                    {
                        printf("\nNo logs currently in the system\n");
                    }
                    else
                    {
                        printf("\nSETTINGS:\n   M=%d\n   N=%d\n   K=%d\n",m, n, k);    
                        displayLogs(games);     
                    }
                    break;

                case 4 : /* Save logs */
                    if(games == NULL || games->size < 1)
                    {
                        printf("\nNo logs to save\n");
                    }
                    else if(saveLogs(games, m, n, k) != -1)
                    {
                        printf("\nLogs saved\n");
                        freeLinkedList(games, &freeGame);
                        games = createLinkedList(); /*refresh the linked list*/
                    }            
                    else
                    {
                        printf("\nFailed to save logs\n");
                    }
                    break;

                case 5 : /* Exit */
                    printf("\ngoodbye...\n\n");
                    freeLinkedList(games, &freeGame);
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
void playGame(Board* board, LinkedList* log)
{ 
    Log* thisLog; 
    int err, xx, yy, option, turn = 0, winner;
    int playing = TRUE; 
    char player = 'X';
    char location[LOCATION_LEN];
    while(playing == TRUE)
    {
        printf("\n");
        displayBoard(board);
        printf("\nPLAYER %c's TURN\n\n", player);
        turn++;

        /* sub menu */
        printf("1: Take turn\n2: Quit\n");
        option = readInt("--> ", 1, 2);
        switch(option)
        {
            case 1 : /* Take turn */

                do /* keep reading coords until valid */
                {
                    readCoords(&xx, &yy);
                    err = insertMove(board, player, xx, yy);
                } 
                while(err == -1);

                sprintf(location, "(%d,%d)", xx, yy);              

                /* Update log */ 
                thisLog = (Log*)malloc(sizeof(Log));
                thisLog->turn = turn;
                thisLog->player = player;
                strcpy(thisLog->location, location);
    
                insertLast(log, thisLog);
                thisLog = NULL;       
 
                /* Check for winner */
                winner = findWinner(board);
                if(winner != 0)
                {
                    printf("\n");
                    displayBoard(board);
                    playing = FALSE;
                    printf("\n------------------");
                    if(winner == 1)
                    {   
                        printf("\n| PLAYER X WINS! |\n");
                    }
                    else
                    {
                        printf("\n| PLAYER O WINS! |\n");
                    }
                    printf("------------------\n");
                } 
                break;

            case 2 : /* Quit */
                printf("\nDRAW!\n");
                playing = FALSE;
                break;
        }

        /* Swap player turn */
        if(player == 'X')
        {
            player = 'O';
        }
        else
        {
            player = 'X';
        }
    } 
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

/*TODO*/
void displayLogs(LinkedList* listOfGames)
{
    int game = 0;
    LinkedListNode* thisNode = listOfGames->head;
    while(thisNode != NULL)
    {
        game++;
        printf("\nGAME %d:", game);
        printLinkedList(thisNode->data, &printLog); 
        thisNode = thisNode->next;
    }
}
