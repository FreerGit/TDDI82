CC := g++
FLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Werror -Weffc++
LIB := -lsfml-window -lsfml-graphics -lsfml-system


a.out:	main.o file_handler.o
	$(CC) $(FLAGS) file_handler.o main.o $(LIB)

file_handler.o:	file_handler.cpp file_handler.h
	$(CC) $(FLAGS) -c file_handler.cpp

main.o:	main.cpp
	$(CC) $(FLAGS) -c main.cpp $(LIB)
