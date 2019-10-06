/* ****************************************************************************
 * FILE:        board.c
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Responsible for representing the board structure using a 2d 
 *              array of integers. The potential values of an element and their
 *              representation are given below:
 *                  0 = empty
 *                  1 = X for player 1
 *                  2 = O for player 2 
 *              Contains functions for creating a board, checking if a 
 *              space is occupied, inserting a move, and finding a winner. 
 *
 * LAST MOD:    28/09/19 
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "linked_list.h"

/* ****************************************************************************
 * NAME:        createBoard
 *
 * PURPOSE:     Allocates and initializes a new board using a struct.
 *              Returns a pointer to the board struct.
 *
 * IMPORT:      width, height, inNumMatchingTiles (integers)
 * EXPORT:      board (Board pointer)
 * ***************************************************************************/
Board* createBoard(int width, int height, int inNumMatchingTiles)
{
    int ii;
    Board* board;

    /* Validate imports */
    if((width < LOWER || width > UPPER) ||   
       (height < LOWER || height > UPPER) ||
       (inNumMatchingTiles < LOWER || inNumMatchingTiles > UPPER))
    {
        board = NULL;
    }
    else
    {
        /* Initialise board and array */
        board = (Board*)malloc(sizeof(Board));
        board->map = (int**)malloc(sizeof(int*) * height);
        for(ii = 0; ii < height; ii++)
        {
            board->map[ii] = (int*)malloc(sizeof(int) * width);
            memset(board->map[ii], 0, sizeof(int) * width);
        }
        board->width = width;
        board->height = height;
        board->numMatchingTiles = inNumMatchingTiles;
    }

    return board;
}

/* ****************************************************************************
 * NAME:        insertMove
 *
 * PURPOSE:     To insert a player's move into the board map array.
 *              i.e. if player 1 inputs (0,0), a 1 will be added to element
 *              [0][0] of the array.
 *
 * IMPORT:      board (Board pointer), player (char), coords - xx/yy (integers)
 * EXPORT:      result (integer - 0 if success, -1 if collision/error)
 * ***************************************************************************/
int insertMove(Board* board, char player, int xx, int yy)
{
    int result = 0;

    /* Validation (zero-based) */
    if((xx < 0 || xx >= board->width) ||
       (yy < 0 || yy >= board->height) ||
       (player != 'X' && player != 'O'))
    {
        printf("\ninvalid coordinats: (%d,%d)\n", xx, yy);
        result = -1;
    }
    else if(board->map[yy][xx] != 0) /* Collision checking */
    {
        printf("\nposition (%d,%d) is taken\n", xx, yy);
        result = -1;
    }
    else /* Make insertion */
    {
        if(player == 'X')
        {
            board->map[yy][xx] = 1;
        }
        else
        {
            board->map[yy][xx] = 2;
        }
    }

    return result;
}

/* ****************************************************************************
 * NAME:        findWinner
 *
 * PURPOSE:     Returns an integer if a winner is determined (1 for player X,
 *              2 for player O). Returns 0 if no winner is found.
 *              Winner is determined by a player who has K items in a row
 *              on the array.      
 *
 * IMPORT:      board (Board pointer)
 * EXPORT:      winner (integer)
 * ***************************************************************************/
int findWinner(Board* board)
{
    return 0;
}

/* ****************************************************************************
 * NAME:        destroyBoard
 *
 * PURPOSE:     Free's all malloced memory comprising the board.
 *
 * IMPORT:      board (Board pointer)
 * EXPORT:      none
 * ***************************************************************************/
void destroyBoard(Board* board)
{
    int ii;
    for(ii = 0; ii < board->height; ii++)
    {
        free(board->map[ii]);
    }   
    free(board->map);
    free(board);
    board = NULL;
}

/* Used as function pointers for linked lists */

/*TODO*/
void freeGame(void* game)
{
    LinkedList* gameLogs = (LinkedList*)game;
    freeLinkedList(gameLogs, &freeLog);
}

/*TODO*/
void printLog(void* log)
{
    Log* lg = (Log*)log;
    printf("\n   Turn: %d\n", lg->turn);
    printf("   Player: %c\n", lg->player);
    printf("   Location: %s\n", lg->location);
}

/*TODO*/
void freeLog(void* log)
{
    free((Log*)log);
}
