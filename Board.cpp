// MCS 360 Project 5 by <Gierach, Thomas> and <Yee, Justin>
#include "Board.h"
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <random>

Board::Board(int d, int n): number(n) { //dimension, //number
	
	for (int i = 0; i < d; i++) {
		vector< int > temp;
		for (int j = 0; j < d; j++) {
			int num = rand() % n;
			temp.push_back(num);	
		}
		board.push_back(temp);
	}	
}

int Board::dimension() {
	
	return board.size();
}
int Board::hcount(int row, int column)
/*
//so, we get an index in the row, 
1)we go left until there is not a match
2)we go right until there is not a match
3)returns a count

//0 2 2 2 0, count = 1
//- m m - -, count = 2
//- m m m -, count = 3
return count
*/
{	
	int count = 1, n = 1, value = board[row][column];
	//count = check for whether numbers are consecutive, n = used to increment the column, value = element in the board
	//This checks for consecutive numbers to the left
	while (value == board[row][column] && column - n >= 0) {
		if (board[row][column - n] == value) {
			count++;
		}
		value = board[row][column - n];
		n++;
	}
	value = board[row][column]; //go back to original position at the board and prepare to check right
	n = 1; //sets the increment back to the original position

	//This checks for consecutive numbers to the right
	while (value == board[row][column] && column + n < board.size()) {
		if (board[row][column + n] == value) {
			count++;
		}
		value = board[row][column + n];
		n++;
	}
	return count;
	
}

int Board::vcount(int row, int column)
{
	int count = 1, n = 1, value = board[row][column];
	//count = check for whether numbers are consecutive, n = used to increment the column, value = element in the board
	//This checks above the original position in the column
	while (value == board[row][column] && row - n >= 0) {
		if (board[row - n][column] == value) {
			count++;
		}
		value = board[row - n][column];
		n++;
	}
	value = board[row][column]; //go back to original position at the board and prepare to check down
	n = 1; //sets the increment back to the original position
	//This checks below the original position in the column
	while (value == board[row][column] && row + n < board.size()) {
		if (board[row + n][column] == value) {
			count++;
		}
		value = board[row + n][column];
		n++;
	}
	return count;
}

/*returns the number of consecutive same numbers
//on the column that contains
//the number at the given row and column col.*/

void Board::shift(int row, int column) 
{
	for (int r = 0; r < row + 1; ++r) {
		board[r][column] = rand() % this->number;
	}
}
/*takes on input a row and a column index,
//replaces all numbers in the same column col at
//and above the given row by random numbers
//in the range: 0 to n - 1.*/
bool Board::swap(int row, int column) 
{
	
	int a, b, c;
	if (row > 0) 
	{
		//cout << "attempting to swap above" << endl;
		a = board[row][column];
		b = board[row - 1][column];
		//cout << "original:" << a << endl;
		//cout << "replacement above: " << b << endl;
		c = a;
		//cout << c << endl;
		board[row][column] = b;
		//cout << "replacement now in original's place " << a << endl;
		board[row - 1][column] = c;
		//cout << "original now in replacement's place " << b << endl;
		
		//cout << "hcount: " << this->hcount(row, column) << endl;
		//cout << "vcount: " << this->vcount(row, column) << endl;
		if (this->hcount(row, column) >= 3 || this->vcount(row, column) >= 3) {
			//cout << "returning true: " << endl;
			return true;
		}
		else {
			a = board[row][column];
			b = board[row - 1][column];
			c = a;
			board[row][column] = b;
			board[row - 1][column] = c;
		}

	}
	if (row < this->dimension() - 1) {
		//cout <<"attempting to swap below" << endl;

		a = board[row][column];
		b = board[row + 1][column];
		//cout << "original:" << a << endl;
		//cout << "replacement below:" << b << endl;
		c = a;
		//cout << c << endl;
		board[row][column] = b;
		//cout << "replacement now in original's place " << a << endl;
		board[row + 1][column] = c;
		//cout << "original now in replacement's place " << b << endl;

		//cout << "hcount: " << this->hcount(row, column) << endl;
		//cout << "vcount: " << this->vcount(row, column) << endl;

		if (this->hcount(row, column) >= 3 || this->vcount(row, column) >= 3) {
			//cout << "returning true: " << endl;
			return true;
		}
		else {
			a = board[row][column];
			b = board[row + 1][column];
			c = a;
			board[row][column] = b;
			board[row + 1][column] = c;
		}
	}
	if (column > 0) {
		//cout << "attempting to swap to the left" << endl;
		a = board[row][column];
		b = board[row][column - 1];
		//cout << "original:" << a << endl;
		//cout << "replacement to the right" << b << endl;
		c = a;
		//cout << c << endl;
		board[row][column] = b;
		//cout << "replacement now in original's place " << a << endl;
		board[row][column - 1] = c;
		//cout << "original now in replacement's place " << b << endl;
		//cout << "hcount: " << this->hcount(row, column) << endl;
		//cout << "vcount: " << this->vcount(row, column) << endl;

		if (this->hcount(row, column) >= 3 || this->vcount(row, column) >= 3) {
			//cout << "returning true: " << endl;
			return true;
		}
		else {
			a = board[row][column];
			b = board[row][column - 1];
			c = a;
			board[row][column] = b;
			board[row][column - 1] = c;
		}

	}
	if (column < this->dimension() - 1) {
		//cout << "attempting to swap to the right" << endl;
		a = board[row][column];
		b = board[row][column + 1];
		//cout << "original:" << a << endl;
		//cout << "replacement to the left" << b << endl;
		c = a;
		//cout << c << endl;
		board[row][column] = b;
		//cout << "replacement now in original's place " << a << endl;
		board[row][column + 1] = c;
		//cout << "original now in replacement's place " << b << endl;
		//cout << "hcount: " << this->hcount(row, column) << endl;
		//cout << "vcount: " << this->vcount(row, column) << endl;
		if (this->hcount(row, column) >= 3 || this->vcount(row, column) >= 3) {
			cout << "returning true: " << endl;
			return true;
		}
		else {
			a = board[row][column];
			b = board[row][column + 1];
			c = a;
			board[row][column] = b;
			board[row][column + 1] = c;
		}
	}
	
	return false;
}

ostream& operator<<(ostream& os, Board& bd) {
	int d = bd.dimension();
	
	for (int i = 0; i < d; i++) 
	{
		for (int j = 0; j < d; j++) 
		{
			os << bd.board[i][j] << " ";		
		}
		os<<endl;
	}

	return os;
}