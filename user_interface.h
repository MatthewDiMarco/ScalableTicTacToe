/* ****************************************************************************
 * FILE:        user_interface.h 
 * CREATED:     29/08/19
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Header file for user_interface.c
 *
 * LAST MOD:    12/10/19 
 * MOD BY:      Matthew Di Marco
 * ***************************************************************************/
#include "board.h"
#include "linked_list.h"

/** 
 * Constants 
 */

/* The number of option available in the main menu. */
#ifndef EDITOR
#define NUM_OPTIONS 5
#endif

/* Editor mode will have an extra 6th option for editing settings. */
#ifdef EDITOR
#define NUM_OPTIONS 6
#endif

/**
 * Structs and typedefs
 */

#ifndef UI
#define UI

/**
 * Stores details of a player's move
 */
typedef struct 
{
    int turn;
    char player;
    char location[LOCATION_LEN]; /* e.g. "(xxx,yyy)" */
} Log;

#endif

/** 
 * Prototype declarations 
 */

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
void mainMenu(char* settingsFileName);

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
void playGame(Board* board, LinkedList* log);

/* ****************************************************************************
 * NAME:        displayBoard
 *
 * PURPOSE:     To display the contents of a board to the terminal.
 *
 * IMPORTS:     board (Board pointer) 
 * EXPORTS:     none
 * ***************************************************************************/
void displayBoard(Board* board);

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
void displayLogs(LinkedList* listOfGames);

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
void freeGame(void* game);

/* ****************************************************************************
 * NAME:        freeLog
 *
 * PURPOSE:     The address of this function is passed through the generic 
 *              linked list to free malloc'd log structs.
 *
 * IMPORTS:     log (generic pointer)
 * EXPORTS:     none
 * ***************************************************************************/
void freeLog(void* log);

/* ****************************************************************************
 * NAME:        printLog
 *
 * PURPOSE:     The address of this function is passed through the generic 
 *              linked list when printing log structs.
 *
 * IMPORTS:     log (generic pointer)
 * EXPORTS:     none
 * ***************************************************************************/
void printLog(void* log);
