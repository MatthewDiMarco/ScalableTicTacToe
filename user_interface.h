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
 * macros and constants 
 */

/* the number of option available in the main menu */
#define NUM_OPTIONS 5 

/* the number of chars in a log string */
#define LOG_SIZE 37

/* prototype declarations */

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
void displayLogs(LinkedList* games);

/* ... */
void freeGame(void* logs);

/* ... */
void printLog(void* string);

/* ... */
void freeLog(void* string);
