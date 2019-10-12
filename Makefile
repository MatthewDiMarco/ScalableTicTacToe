##
 # FILE: 		Makefile
 # AUTHOR:		Matthew Di Marco
 # CREATED:		22/09/19
 # -----
 # MODIFIED:	22/09/19
 # BY			Matthew Di Marco
 # -----
 # PURPOSE:		Makefile for the 'TicTacToe' C game.
 # 				In addition to normal compilation, there exists three seperate 
 # 				conditional compilations:
 # 					1) Debug: debug information is enabled.
 # 					2) Secret: log files cannot be saved.
 # 					3) Editor: settings variables can be modified @ runtime. 
##


# variables

CC 			= gcc
CFLAGS 		= -Wall -ansi -pedantic -Werror
OBJ 		= main.o user_input.o user_interface.o file_manager.o board.o linked_list.o 
OBJ_TEST_LL = linked_list.o LinkedListTest.o
OBJ_TEST_BR = board.o BoardTest.o
EXEC 		= TicTacToe
EXEC_LL     = test_ll
EXEC_BR     = test_board


# conditional compilation

ifdef DEBUG
CFLAGS += -g
DEBUG : clean $(EXEC)
endif

ifdef SECRET
CFLAGS += -D SECRET=1
SECRET : clean $(EXEC)
endif

ifdef EDITOR
CFLAGS += -D EDITOR=1
EDITOR : clean $(EXEC)
endif


# rules - production code

$(EXEC) : $(OBJ)
		$(CC) $(OBJ) -o $(EXEC)
 
main.o : main.c user_interface.h
		$(CC) main.c -c $(CFLAGS)

user_input.o : user_input.c user_input.h
		$(CC) user_input.c -c $(CFLAGS)

user_interface.o : user_interface.c user_interface.h
		$(CC) user_interface.c -c $(CFLAGS)

file_manager.o : file_manager.c file_manager.h linked_list.h 
		$(CC) file_manager.c -c $(CFLAGS)

board.o : board.c board.h linked_list.h
		$(CC) board.c -c $(CFLAGS)

linked_list.o : linked_list.c linked_list.h
		$(CC) linked_list.c -c $(CFLAGS)


# rules - test code

tests : $(OBJ_TEST_LL) $(OBJ_TEST_BR) 
		$(CC) $(OBJ_TEST_LL) -o $(EXEC_LL)
		$(CC) $(OBJ_TEST_BR) -o $(EXEC_BR)

LinkedListTest.o : LinkedListTest.c linked_list.h
		$(CC) LinkedListTest.c -c $(CFLAGS)

BoardTest.o : BoardTest.c board.h
		$(CC) BoardTest.c -c $(CFLAGS)


# run / clean rules

run :
		./$(EXEC) settings.txt

runVal : 
		valgrind ./$(EXEC) settings.txt

runTests :
		valgrind ./$(EXEC_LL)
		valgrind ./$(EXEC_BR)

clean :
		rm -f $(EXEC) $(EXEC_LL) $(EXEC_BR) *.o

cleanLogs :	
		rm -f MNK*.log
