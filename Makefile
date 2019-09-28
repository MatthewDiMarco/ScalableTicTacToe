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

CC 		= gcc
CFLAGS 	= -Wall -ansi -pedantic -Werror
OBJ 	= main.o user_input.o user_interface.o file_manager.o board.o linked_list.o 
EXEC 	= TicTacToe

# conditional compilation

ifdef DEBUG
CFLAGS += -g
DEBUG : clean $(EXEC)
endif

ifdef SECRET
endif

ifdef EDITOR
endif

# rules

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

run :
		./$(EXEC) settings.txt

runVal : 
		valgrind ./$(EXEC) settings.txt

# all should fail except for the last two
testSettings : 
		./$(EXEC) TestSettingsFiles/format1	
		./$(EXEC) TestSettingsFiles/format2
		./$(EXEC) TestSettingsFiles/format3
		./$(EXEC) TestSettingsFiles/negative
		./$(EXEC) TestSettingsFiles/duplicates
		./$(EXEC) TestSettingsFiles/missing
		./$(EXEC) TestSettingsFiles/empty
		./$(EXEC) TestSettingsFiles/idontexist
		echo 5 | ./$(EXEC) TestSettingsFiles/backwards 
		echo 5 | ./$(EXEC) TestSettingsFiles/lowercase

clean :
		rm -f $(EXEC) $(OBJ)

