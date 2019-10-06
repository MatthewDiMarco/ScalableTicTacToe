/* ****************************************************************************
 * FILE:        user_interface.h 
 * CREATED:     29/08/19
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains definitions of prototypes and macros used inside
 *              of user_interface.c
 *
 * LAST MOD:    28/09/19 
 * MOD BY:      Matthew Di Marco
 * ***************************************************************************/
#include "board.h"
#include "linked_list.h"

/** 
 * Macros and Constants 
 */

/* the number of option available in the main menu */
#define NUM_OPTIONS 5 

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

/* ... */
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

/* ... */
void displayLogs(LinkedList* listOfGames);
