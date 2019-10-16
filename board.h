/* ****************************************************************************
 * FILE:        board.h
 * CREATED:     27/09/19
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Header file for board.c
 *
 * LAST MOD:    12/10/19 
 * MOD BY:      Matthew Di Marco
 * ***************************************************************************/

/**
 * Constants
 */

/* The upper and lower bound values (inclusive) for the game settings */
#define UPPER 999
#define LOWER 3

/* The number of chars to be in a location string for the Log struct */
#define LOCATION_LEN 9

/**
 * Structs and typedefs
 */

#ifndef BOARD
#define BOARD

/**
 * Contains all dimension details of the board, and a map (matrix).
 * Use the createBoard() function to allocate memory for the 2d array.
 */
typedef struct 
{
    int width;
    int height;
    int numMatchingTiles;
    int** map;
} Board;

#endif

/**
 * Prototype declarations
 */

/* ****************************************************************************
 * NAME:        createBoard
 *
 * PURPOSE:     Allocates and initializes a new board using a struct.
 *              Returns a pointer to the board struct.
 *
 * IMPORT:      width, height, inNumMatchingTiles (integers)
 * EXPORT:      board (Board pointer)
 * ***************************************************************************/
Board* createBoard(int width, int height, int inNumMatchingTiles);

/* ****************************************************************************
 * NAME:        insertMove
 *
 * PURPOSE:     To insert a player's move into the board map array.
 *              i.e. if player 1 inputs (0,0), a 1 will be added to element
 *              [0][0] of the array.
 *
 * IMPORT:      board (Board pointer), player (char), coords - xx/yy (integers)
 * EXPORT:      result (integer - 0 if success, -1 if collision)
 * ***************************************************************************/
int insertMove(Board* board, char player, int xx, int yy);

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
 *
 * IMPORT:      board (Board pointer)
 * EXPORT:      winner (integer)
 * ***************************************************************************/
int findWinner(Board* board);

/* ****************************************************************************
 * NAME:        destroyBoard
 *
 * PURPOSE:     Free's all malloced memory making up the board.
 *
 * IMPORT:      board (Board pointer)
 * EXPORT:      none
 * ***************************************************************************/
void destroyBoard(Board* board);
