## m-n-k Tic-Tac-Toe

An implementation of the game 'tic-tac-toe' written in C89, but the Width and
Height values of the board are scalable, as well as the number of tile matches
required to win (k).

## Command line

Once compiled, the program can be executed along with a settings file, using the below command:

        `./TicTacToe settings.txt`
       
Note that any file in the same directory can be used, and does not explicitly need to be named settings.

## Settings (input) file

Before running, a settings file must be written. The settings file should contain three lines, each with one of the three settings: M (width), N (height) and K (number of matching tiles required to win). The program ignores the order and case sensitivity of the filr contents, but there should not be any missing or duplicate settings. An example of a valid settings file is given below:

    ```
    M=5
    N=3
    K=3
    ```

## Interacting with the menu 

Upon successful loading of the settings file, a list will be displayed featuring 5 (or 6) different options, depending on the compilation type. The user will enter an integer next to the --> arrow beneath the list, and the function associated with the number in the list is executed. Entering non-integer or out-of-range values will result in an error message, and re-printing of the menu.

## Board output

If option 1 is selected from the main menu, a board is constructed and the displayBoard() function is called to draw up the rows and columns. An example of what the board will look like is given below:

    ```   
       0   1   2   3   4
    =======================
    ||   | X |   |   |   || 0
    ||-------------------|| 
    ||   |   | O |   |   || 1
    ||-------------------||
    ||   | X | X | O |   || 2
    ||-------------------||
    ||   |   |   |   |   || 3
    ||-------------------||
    ||   |   |   |   |   || 4
    =======================
    ```

Note that each row and column are numbered. This decision was made to enable the user to more quickly make insertions on the board, and to prevent damaging usability from rising N and M values.

## Saving logs

An example of the contents in a saved log file is given below (same format when printing from menu).

    ```
    SETTINGS
       M=5
       N=5
       K=3

    GAME 1:
       Turn: 1
       Player: X
       Location: (2,3)

       Turn: 2
       Player: O
       Location: (2,4)

    GAME 2:
       Turn: 1
       Player: X
       Location: (4,1)
    ```
