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

/* static prototype declarations */
static int checkAdjacentRec(Board* board, int rIdx, int cIdx, int k);
static int checkBeneathRec(Board* board, int rIdx, int cIdx, int k);
static int checkDiagonalUpRec(Board* board, int rIdx, int cIdx, int k);
static int checkDiagonalDownRec(Board* board, int rIdx, int cIdx, int k);

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
    int ii, jj, winner = 0, k = board->numMatchingTiles;    

    /*Check along all rows*/
    ii = 0;
    while(ii < board->height && winner == 0)
    {
        jj = 0;
        while(jj < board->width && winner == 0)
        {
            /*Is there a potential win here? If not, skip*/
            if(board->map[ii][jj] != 0)
            {
                /*Check match k times in a row from left to right*/
                winner = checkAdjacentRec(board, ii, jj, k);

                /*Check match k times in a row from this cell down*/
                if(winner == 0)
                {
                    winner = checkBeneathRec(board, ii, jj, k);

                    /*Check diagonal up*/
                    if(winner == 0)
                    {
                        winner = checkDiagonalUpRec(board, ii, jj, k);

                        /*Check diagonal down*/
                        if(winner == 0)
                        {
                            winner = checkDiagonalDownRec(board, ii, jj, k);
                        }
                    }
                }
            }
            jj++;
        }
        ii++;
    }   
    return winner;
}

/* ... */
static int checkAdjacentRec(Board* board, int rIdx, int cIdx, int k)
{   
    int winner = 0;
    int thisElement = board->map[rIdx][cIdx];
    if(cIdx < board->width - 1) /*Check we aren't going out of bounds*/
    {
        if(thisElement == board->map[rIdx][cIdx + 1]) /*Check adjacent*/
        {
            if(k > 2) /*Still more to check?*/
            {
                winner = checkAdjacentRec(board, rIdx, cIdx + 1, k - 1);
            }
            else /*Winner found*/
            {
                winner = thisElement;
            }
        }
    }
    return winner;
}

/* ... */
static int checkBeneathRec(Board* board, int rIdx, int cIdx, int k)
{   
    int winner = 0;
    int thisElement = board->map[rIdx][cIdx];
    if(rIdx < board->height - 1)
    {
        if(thisElement == board->map[rIdx + 1][cIdx]) /*Check beneath*/
        {
            if(k > 2) /*Still more to check?*/
            {
                winner = checkBeneathRec(board, rIdx + 1, cIdx, k - 1);
            }
            else /*Winner found*/
            {
                winner = thisElement;
            }
        }
    }
    return winner;
}

/* ... */
static int checkDiagonalUpRec(Board* board, int rIdx, int cIdx, int k)
{   
    int winner = 0;
    int thisElement = board->map[rIdx][cIdx];
    if((rIdx > 0) && (cIdx < board->width - 1))
    {
        if(thisElement == board->map[rIdx - 1][cIdx + 1]) /*Check up-right*/
        {
            if(k > 2) /*Still more to check?*/
            {
                winner = checkDiagonalUpRec(board, rIdx - 1, cIdx + 1, k - 1);
            }
            else /*Winner found*/
            {
                winner = thisElement;
            }
        }
    }
    return winner;
}

/* ... */
static int checkDiagonalDownRec(Board* board, int rIdx, int cIdx, int k)
{
    int winner = 0;
    int thisElement = board->map[rIdx][cIdx];
    if((rIdx < board->height - 1) && (cIdx < board->width - 1))
    {
        if(thisElement == board->map[rIdx + 1][cIdx + 1]) /*Check down-right*/
        {
            if(k > 2) /*Still more to check?*/
            {
                winner = checkDiagonalDownRec(board, rIdx + 1, cIdx + 1, k - 1);
            }
            else /*Winner found*/
            {
                winner = thisElement;
            }
        }
    }
    return winner; 
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
