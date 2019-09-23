/* ****************************************************************************
 * FILE:        user_interface.c
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains functions for outputting the central menu and sub
 *              menus. Also contains functionality for displaying various 
 *              graphics to the terminal, such as the tic-tac-toe N*M board.
 *
 * LAST MOD:    23/09/19 
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user_interface.h"
#include "user_input.h"
#include "file_manager.h"
#include "game_rules.h"
#include "linked_list.h" 

/* ****************************************************************************
 * NAME:        mainMenu
 * PURPOSE:     To print a list of options to the terminal which the user can
 *              select from. The appropriate function will be called based
 *              on what the user selected.
 * IMPORTS:     settingsFileName (string)
 * EXPORTS:     none
 * ***************************************************************************/
void mainMenu(char* settingsFileName)
{ 
    int option, m, n, k, ii, running;
    char* ops[] = { "\n1: Start new game\n", 
                    "2: View settings\n",
                    "3: View logs\n",
                    "4: Save logs\n",
                    "5: Exit\n\n" };

    /* validate settings file */
    if(readSettings(settingsFileName, &m, &n, &k) == -1)
    {
        printf("failed to read %s: shutting down...\n\n", settingsFileName);
    }
    else /* if settings are ok, enter main loop */
    {
        printf("\n---Welcome---\n");
        running = TRUE;
        do
        {
            /* print menu */
            for(ii = 0; ii < NUM_OPTIONS; ii++)
            {
                printf(ops[ii]);
            }

            /* get user input and execute option */
            option = readInt("Select an option:\n--> ", 1, NUM_OPTIONS);
            switch(option)
            {
                case 1 :
                    printf("\nfunction (1) not implemented yet\n");            
                    break;

                case 2 :
                    printf("\nSETTINGS:\n---------\n");
                    printf("M=%d\nN=%d\nK=%d\n---------\n", m, n, k);
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
