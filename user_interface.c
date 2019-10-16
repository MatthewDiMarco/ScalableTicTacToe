/* ****************************************************************************
 * FILE:        user_interface.c
 * CREATED:     29/08/19
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains functions for outputting the central menu and sub
 *              menus. Also contains functionality for displaying different 
 *              graphics to the terminal, such as the TicTacToe board.
 *
 * LAST MOD:    12/10/19
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

    char* ops[NUM_OPTIONS];
    ops[0] = "1: Start new game\n";
    ops[1] = "2: View settings\n";
    ops[2] = "3: View logs\n";
    ops[3] = "4: Save logs\n";
    ops[4] = "5: Exit\n";

    /* Extra op for EDITOR mode */
    #ifdef EDITOR
    ops[5] = "6: Edit settings\n";
    #endif

    /* Validate settings file */
    if(readSettings(settingsFileName, &m, &n, &k) == -1)
    {
        printf("failed to read %s: shutting down...\n\n", settingsFileName);
    }
    else /* If settings are ok, enter main loop */
    {
        printf("\n  ---Welcome---\n");
        games = createLinkedList();
        running = TRUE;
        do
        {
            /* Print menu */
            printf("\nSelect an option\n----------------\n");
            for(ii = 0; ii < NUM_OPTIONS; ii++)
            {
                printf(ops[ii]);
            }

            /* Get user input and execute option */
            option = readInt("--> ", 1, NUM_OPTIONS);
            switch(option)
            {
                case 1 : /* Start new game */  
                    log = createLinkedList(); /* Capture moves for this game */
                    playGame(createBoard(m, n, k), log);
        
                    /** 
                     * Add the previous game's log to the list of games.
                     * Set the log to null so it's ready for another game, and 
                     * do NOT free the log (we want to keep it for displaying/
                     * saving). All game logs will be free'd when we destroy
                     * 'games' at the end of runtime.
                     * Only free log if no moves were made.
                     */
                    if(log->size > 0) /* were any moves made? */
                    {
                        insertLast(games, log); 
                    }
                    else
                    {
                        free(log);
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
                    #ifndef SECRET
                    if(games == NULL || games->size < 1) /* Any logs to save? */
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
                    #endif

                    /* Prevent saving in secret mode */
                    #ifdef SECRET
                    printf("\nYou are playing in SECRET mode: cannot save logs.\n");
                    printf("To regain this ability, recompile normally.\n");
                    #endif

                    break;

                case 5 : /* Exit */
                    printf("\ngoodbye...\n\n");
                    freeLinkedList(games, &freeGame);
                    running = FALSE;            
                    break;

                #ifdef EDITOR
                case 6 : /* Edit mnk */
                    readMNK(&m, &n, &k);
                    break;
                #endif

                default : 
                    /* can't get here */ 
                    break;
            }
        }
        while(running == TRUE);
    }
}

/* ****************************************************************************
 * NAME:        playGame
 *
 * PURPOSE:     This function acts as an interface between the board struct
 *              (game) and the user. From here, two players (X and O) can 
 *              enter coordinates on the board and compete in a game.
 *
 *              The appropriate functions are called to print the board, log
 *              moves to the imported list and to check for a winner each
 *              iteration.
 *                  
 *              Player turns are tracked using the 'player' char variable, and
 *              swap between 'O' and 'X' each iteration, with the starting
 *              default being player X.
 *
 * IMPORTS:     board (Board pointer), log (LinkedList pointer)
 * EXPORTS:     none
 * ***************************************************************************/
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
        printf("\nPLAYER %c's TURN\n", player);
        turn++;

        /* Sub menu */
        err = -1;
        do
        {
            printf("\n1: Take turn\n2: Quit\n");
            option = readInt("--> ", 1, 2);
            if(option != 0) /* If an error occured, 0 is returned */
            {
                err = 0; /* Exit loop */
            }
        }
        while (err == -1);
        switch(option)
        {
            case 1 : /* Take turn */

                err = -1;
                do /* Keep reading coords until valid */
                {
                    if(readCoords(&xx, &yy) != -1)
                    {
                        err = insertMove(board, player, xx, yy);
                        if(err == -1)
                        {
                            printf("\nPosition (%d,%d) is out of bounds or taken\n", xx, yy);
                        }
                    }
                } 
                while(err == -1); 

                /* Update log */ 
                thisLog = (Log*)malloc(sizeof(Log));
                thisLog->turn = turn;
                thisLog->player = player;
                sprintf(location, "(%d,%d)", xx, yy);           
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
 * PURPOSE:     To display the contents of the board to the terminal.
 *
 * IMPORTS:     board (Board pointer) 
 * EXPORTS:     none
 * ***************************************************************************/
void displayBoard(Board* board)
{
    int ii, jj;

    /* print upper border */
    printf(" ");
    for(ii = 0; ii < board->width; ii++)
    {
        printf(" %2d ", ii); /*print numbers*/
    }
    printf("\n==");
    for(ii = 0; ii < board->width; ii++) 
    {
        printf("===="); /*print bar*/
    }
    printf("=\n");

    /* Print board */
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
        printf("| %2d\n", ii);
       
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

/* ****************************************************************************
 * NAME:        displayLogs
 *
 * PURPOSE:     Takes a list of log struct lists (linked list of linked 
 *              lists). Each list inside the imported list is a 'game', and
 *              contains sequence of logs. This function prints the logs of
 *              every game, separating them with the header 'GAME X'.
 *
 * IMPORTS:     listOfGames (LinkedList pointer)
 * EXPORTS:     none
 * ***************************************************************************/
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

/* ****************************************************************************
 * NAME:        freeGame
 *
 * PURPOSE:     The address of this function is passed to the generic linked
 *              list and serves the purpose of freeing a 'game' (linked list
 *              of log structs).
 *              
 *              This function is imported into freeLinkedList() when exiting
 *              the program to free all of the games in the game list (before
 *              the list of games itself is free'd).
 *
 * IMPORTS:     game (generic pointer)
 * EXPORTS:     none
 * ***************************************************************************/
void freeGame(void* game)
{
    LinkedList* gameLogs = (LinkedList*)game;
    freeLinkedList(gameLogs, &freeLog);
}

/* ****************************************************************************
 * NAME:        freeLog
 *
 * PURPOSE:     The address of this function is passed through the generic 
 *              linked list to free malloc'd log structs.
 *
 * IMPORTS:     log (generic pointer)
 * EXPORTS:     none
 * ***************************************************************************/
void freeLog(void* log)
{
    free((Log*)log);
}

/* ****************************************************************************
 * NAME:        printLog
 *
 * PURPOSE:     The address of this function is passed through the generic 
 *              linked list when printing log structs.
 *
 * IMPORTS:     log (generic pointer)
 * EXPORTS:     none
 * ***************************************************************************/
void printLog(void* log)
{
    Log* lg = (Log*)log;
    printf("\n   Turn: %d\n", lg->turn);
    printf("   Player: %c\n", lg->player);
    printf("   Location: %s\n", lg->location);
}
