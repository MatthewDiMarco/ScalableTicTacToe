/* ****************************************************************************
 * FILE:        user_interface.h
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains definitions of prototypes and macros used inside
 *              of user_interface.c
 *
 * LAST MOD:    28/09/19 
 * ***************************************************************************/
#include "board.h"

/* macros and constants */

/* the number of option available in the main menu */
#define NUM_OPTIONS 5 

/* typdefs, enums */

/* structs */

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

void playGame(Board* board);

/* ****************************************************************************
 * NAME:        displayBoard
 *
 * PURPOSE:     To display the contents of a board to the terminal.
 *
 * IMPORTS:     board (Board pointer) 
 * EXPORTS:     none
 * ***************************************************************************/
void displayBoard(Board* board);
