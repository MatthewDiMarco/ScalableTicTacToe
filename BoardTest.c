/* ****************************************************************************
 * FILE:        BoardTest.c
 * CREATED:     11/10/19
 * AUTHOR:      Matthew Di Marco
 * 
 * PURPOSE:     Test harness for board.c
 *
 * LAST MOD:    11/10/19
 * MOD BY:      Matthew Di Marco
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "board.h"

int main()
{
    int err;
    Board* board = NULL;
    int mnkData[2][3] = { {3, 3, 3},      /* valid */
                          {4, -1, 5} };    /* invalid k */

    /* CREATING */

    /* test invalid imports */
    printf("Creating Board: ");
    board = createBoard(mnkData[1][0], mnkData[1][1], mnkData[1][2]);
    if(board == NULL)
    {
       printf("PASSED\n");
    }
    else
    {
       printf("FAILED\n");
    }

    /* test valid imports */
    printf("Creating Board (2): ");
    board = createBoard(mnkData[0][0], mnkData[0][1], mnkData[0][2]);
    if(board == NULL || board->map == NULL)
    {
       printf("FAILED\n");
    }
    else if(board->width == mnkData[0][0] &&
            board->height == mnkData[0][1] &&
            board->numMatchingTiles == mnkData[0][2])
    {
       printf("PASSED\n");
    }
    else
    {
        printf("FAILED\n");
    }

    /* INSERT MOVE */

    /* inserting a valid move */
    printf("inserting a move: ");
    insertMove(board, 'X', 2, 2);
    if(board->map[2][2] == 1) /*player 1 should occupy this spot*/
    {
        printf("PASSED\n");
    }
    else
    {
        printf("FAILED\n");
    }

    /* (2) trying to insert into occupied spot */
    printf("Inserting a move (2): ");
    err = insertMove(board, 'O', 2, 2);
    if(err != -1 || board->map[2][2] != 1)
    {
        printf("FAILED\n");
    }
    else
    {
        printf("PASSED\n");
    }

    /* (3) trying to move outside board */
    printf("Inserting a move (3): ");
    err = insertMove(board, 'O', -1, 6);
    if(err != -1)
    {
        printf("FAILED\n");
    }
    else
    {
        printf("PASSED\n");
    }

    /* FINDING A WINNER */

    /* Horizontal */
    printf("Finding a winner ( ~ ): ");
    insertMove(board, 'X', 0, 0);
    insertMove(board, 'X', 0, 1);
    insertMove(board, 'X', 0, 2);
    if(findWinner(board) != 1)
    {
        printf("FAILED\n");
    }
    else
    {
        printf("PASSED\n");
    }

    /* Vertical */
    printf("Finding a winner ( | ): ");
    insertMove(board, 'X', 0, 0);
    insertMove(board, 'X', 1, 0);
    insertMove(board, 'X', 2, 0);
    if(findWinner(board) != 1)
    {
        printf("FAILED\n");
    }
    else
    {
        printf("PASSED\n");
    }

    /* Diagonal Up */
    printf("Finding a winner ( / ): ");
    insertMove(board, 'X', 0, 2);
    insertMove(board, 'X', 1, 1);
    insertMove(board, 'X', 2, 0);
    if(findWinner(board) != 1)
    {
        printf("FAILED\n");
    }
    else
    {
        printf("PASSED\n");
    }

    /* Diagonal Down */
    printf("Finding a winner ( \\ ): ");
    insertMove(board, 'X', 0, 0);
    insertMove(board, 'X', 1, 1);
    insertMove(board, 'X', 2, 2);
    if(findWinner(board) != 1)
    {
        printf("FAILED\n");
    }
    else
    {
        printf("PASSED\n");
    }

    /*FREEING*/

    printf("Free Board: ");
    destroyBoard(board);
    printf("PASSED\n");   
 
    return 0;
}
