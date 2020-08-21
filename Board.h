// MCS 360 Project 5 by <Gierach, Thomas> and <Yee, Justin>
#pragma once
#include <iostream>
#include <ostream>
#include <vector>
using namespace std;

class Player;
//forward declaration of class Player
class Board {
	private:
		int number;
		//defines the range of numbers on the board
		vector<vector <int>> board;
		//defines the dimension of the board
	public:
		Board(int d, int n);
		/*Constructor:
		//takes on input two integers:
		//1)the dimension
		//2)the number n which defines the range of the numbers on the board.
		//The constructor makes a square board of the given dimension with random
		//numbers in the range from 0 to n-1.*/
		int dimension();
		/*returns the dimension of the board, that is:
		//the number of rows and columns.*/
		int hcount(int row, int column);
		/*returns the number of consecutive same
		//numbers on the row that contains the
		//number at the given row and column*/
		int vcount(int row, int column);
		/*returns the number of consecutive same numbers
		//on the column that contains
		//the number at the given row and column col.*/
		void shift(int row, int column);
		/*takes on input a row and a column index,
		//replaces all numbers in the same column col at
		//and above the given row by random numbers
		//in the range: 0 to n - 1.*/
		bool swap(int row, int column);
		/*takes on input the index of a row and the index of a column and it returns a
		//Boolean value on return.
		//tries all four different swaps :
		//trying to swap the(i; j)-th element
		////with(i - 1; j), if i > 0;
		////with(i + 1; j), if i < n - 1;
		////with(i; j - 1), if j > 0; and
		////with(i; j + 1), if j < n - 1.
		//If all possibilities fail to yield a match of
		//at least 3 consecutive numbers on the same row or column, then
		//false is returned,
		//otherwise true is returned at the first successful swap.*/
		friend ostream& operator<<(ostream &os, Board& bd);
		//writes the board to screen, with numbers 
		//separated by one space, taking a new
		//line for every new row.
		friend class Player;
		/*Gives access to class Player to class Board*/
};