/* ****************************************************************************
 * FILE:        main.c
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains the main method for the TicTacToe C game.
 *              The program starts by loading in a settings txt file of format:
 *                  
 *                  M=x  --> board width
 *                  N=y  --> board height
 *                  K=z  --> num of matching tiles in a row to win              
 *              
 *              If an incorrect number of cmd line arguments are supplied
 *              (i.e. > 2 or < 2 ) then an error message is displayed.
 *              Otherwise, the mainMenu() method from user_interface.c 
 *              is called and the settings file name is passed over to it.
 *
 * LAST MOD:    22/09/19 
 * ***************************************************************************/
#include <stdio.h>

#include "user_interface.h"

/* ****************************************************************************
 * NAME:        main()
 * PURPOSE:     To run the program.
 * IMPORTS:     settings file at the cmd line 
 * EXPORTS:     none
 * ***************************************************************************/
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("wrong arguments: format = ./TicTacToe <settings_file.txt>\n");
    }
    else
    {
        mainMenu(argv[1]);
    }
    return 0;
}
