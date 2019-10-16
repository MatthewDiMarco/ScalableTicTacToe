/* ****************************************************************************
 * FILE:        board.c
 * CREATED:     27/09/19
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Responsible for representing the board structure using a 2d 
 *              array of integers. The potential values of an element and their
 *              representation are given below:
 *                  0 = empty
 *                  1 = X for player 1
 *                  2 = O for player 2 
 *
 *              Contains functions for creating a board, inserting a move,
 *              finding a winner, and deallocating (destroying) a board.
 *
 * LAST MOD:    12/10/19
 * MOD BY:      Matthew Di Marco 
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"

/* static prototypes */
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
 * PURPOSE:     To insert a player's move into the 2d board array.
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
        /* out of bounds */
        result = -1;
    }
    else if(board->map[yy][xx] != 0) /* Collision checking */
    {
        /* occupied */
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
 *              Achieved using recursion. Loop through each element, stoping at
 *              ones where the values is not 0. Check the elements at: upper
 *              right, right, lower right, directly beneath. Because we sweep
 *              from left to right, top-down through the array, there is no
 *              need to check the elements behind the current element (already
 *              been checked) 
 *              (see below diagram for visualization, where * is where we check 
 *              from X).
 *
 *
 *                              =============
 *                              |   |   | * |
 *                              -------------
 *                              |   | X | * |
 *                              -------------
 *                              |   | * | * |
 *                              =============
 *
 *              Acknowledgements: This solution was inspired by some code at:
 *              https://codereview.stackexchange.com/questions/116830/check-if-
 *              a-game-of-tic-tac-toe-has-a-winner
 *
 * IMPORT:      board (Board pointer)
 * EXPORT:      winner (integer)
 * ***************************************************************************/
int findWinner(Board* board)
{ 
    int ii, jj, tt, winner, k;

    /**
     * The loop moves from left to right, and from the top down. For each
     * element we stop at, 4 types of 'wins' need to be checked: 
     *      -> Horizontal
     *      -> Vertical
     *      -> Diagonals
     *
     * A recursive function is used for each direction, all with the same
     * signiture. use a loop and an array of function pointers to execute them
     * in a concise, readable manner.
     */
    int (*checkDirection[4])(Board* board, int rIdx, int cIdx, int k);
    checkDirection[0] = &checkAdjacentRec;
    checkDirection[1] = &checkBeneathRec;
    checkDirection[2] = &checkDiagonalUpRec;
    checkDirection[3] = checkDiagonalDownRec;

    /*Check along all rows*/
    winner = 0;
    ii = 0;
    k = board->numMatchingTiles;    
    while(ii < board->height && winner == 0)
    {
        jj = 0;
        while(jj < board->width && winner == 0)
        {
            /*Is there a potential win here? If not, skip*/
            if(board->map[ii][jj] != 0)
            {
                /*Check horizontal, vertical and diagonals*/
                tt = 0;
                while(tt < 4 && winner == 0)
                {
                    winner = (*checkDirection[tt])(board, ii, jj, k);
                    tt++;
                }
            }
            jj++;
        }
        ii++;
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

/**
 * Static recursive implementations for finding a winner
 */

/* ****************************************************************************
 * NAME:        checkAdjacentRec
 *
 * PURPOSE:     Recursively checks if the element to the right matches this
 *              element K times in a row (with k decreasing each recurse).
 *              Once K reaches 2, then do not recurse anymore (just compare
 *              the final two values, and if they're equal, return the winner).
 *
 *              If the method recurses into a border/wall, the recurse stops
 *              and no winner 0 is returned.
 *
 * IMPORT:      board (Board pointer), player (char), coords - xx/yy (integers)
 * EXPORT:      result (integer - 0 if success, -1 if collision/error)
 * ***************************************************************************/
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

/* ****************************************************************************
 * NAME:        checkBeneathRec
 *
 * PURPOSE:     Recursively checks if the element below this one matches this
 *              element K times in a row (with k decreasing each recurse).
 *              Once K reaches 2, then do not recurse anymore (just compare
 *              the final two values, and if they're equal, return the winner).
 *
 *              If the method recurses into a border/wall, the recurse stops
 *              and no winner 0 is returned.
 *
 * IMPORT:      board (Board pointer), player (char), coords - xx/yy (integers)
 * EXPORT:      result (integer - 0 if success, -1 if collision/error)
 * ***************************************************************************/
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

/* ****************************************************************************
 * NAME:        checkAdjacentRec
 *
 * PURPOSE:     Recursively checks if the element to the upper right matches this
 *              element K times in a row (with k decreasing each recurse).
 *              Once K reaches 2, then do not recurse anymore (just compare
 *              the final two values, and if they're equal, return the winner).
 *
 *              If the method recurses into a border/wall, the recurse stops
 *              and no winner 0 is returned.
 *
 * IMPORT:      board (Board pointer), player (char), coords - xx/yy (integers)
 * EXPORT:      result (integer - 0 if success, -1 if collision/error)
 * ***************************************************************************/
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

/* ****************************************************************************
 * NAME:        checkDiagonalDownRec
 *
 * PURPOSE:     Recursively checks if the element to the bottom right matches this
 *              element K times in a row (with k decreasing each recurse).
 *              Once K reaches 2, then do not recurse anymore (just compare
 *              the final two values, and if they're equal, return the winner).
 *
 *              If the method recurses into a border/wall, the recurse stops
 *              and no winner 0 is returned.
 *
 * IMPORT:      board (Board pointer), player (char), coords - xx/yy (integers)
 * EXPORT:      result (integer - 0 if success, -1 if collision/error)
 * ***************************************************************************/
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
