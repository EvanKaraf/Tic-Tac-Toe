TicTacToe: Board.o main.o 
	g++ -o TicTacToe Board.o main.o

main.o: main.cpp
	g++ -c main.cpp

Board.o: Board.cpp Board.h
	g++ -c Board.cpp

clean:
	rm Board.o main.o
