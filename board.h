/* ****************************************************************************
 * FILE:        board.h
 * AUTHOR:      Matthew Di Marco
 * UNIT:        UNIX and C programming (COMP1000)
 *
 * PURPOSE:     Contains definitions of prototypes and macros used inside
 *              of board.h
 *
 * LAST MOD:    28/09/19 
 * ***************************************************************************/

/* constants */

/* The upper and lower bound values (inclusive) for the game settings */
#define UPPER 9
#define LOWER 1

/* typdefs, enums */

#ifndef BOARD
#define BOARD

/* structs */

/* contains the board's array */
typedef struct 
{
    int width;
    int height;
    int numMatchingTiles;
    int** map;
} Board;

#endif

/* prototypes */

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
 * IMPORT:      board (Board pointer), player coords - xx/yy (integers)
 * EXPORT:      result (integer - 0 if success, -1 if collision)
 * ***************************************************************************/
int insertMove(Board* board, int player, int xx, int yy);

/* ****************************************************************************
 * NAME:        findWinner
 *
 * PURPOSE:     Returns an integer if a winner is determined (1 for player 1,
 *              2 for player 2). Returns 0 if no winner is found.
 *              Winner is determined by a player who has K items in a row
 *              on the array.      
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
