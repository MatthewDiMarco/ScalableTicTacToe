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
OBJ 	= main.o user_input.o user_interface.o file_manager.o game_rules.o linked_list.o 
EXEC 	= TicTacToe

# conditional compilation

ifdef DEBUG
CFLAGS += -g
DEBUG : clean $(EXEC1) $(EXEC2)
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

game_rules.o : game_rules.c game_rules.h linked_list.h
		$(CC) game_rules.c -c $(CFLAGS)

linked_list.o : linked_list.c linked_list.h
		$(CC) linked_list.c -c $(CFLAGS)

run :
		./$(EXEC) settings.txt

runVal: 
		valgrind ./$(EXEC) settings.txt

clean:
		rm -f $(EXEC) $(OBJ)

