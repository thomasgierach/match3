// MCS 360 Project 5 by <Gierach, Thomas> and <Yee, Justin>

//#include "..\Common\Board.h"
//#include "..\Common\Player.h"
#include <string>
#include "Player.h"
#include "Board.h"

/*The square board is represented by a vector of rows.
//Each row is a vector of integers.*/

/*test board applies the shift() method on a constructed board,
//in a loop, till there are no matchings of 3 and more are left.
//Then the user is prompted for a row and column index and the
//outcome of the swap is shown. If the match is successful,
//then the shift() method is applied to remove
//the matchings of 3 and more.
//The score counts the number of shifts executed.
//If the swap() returns false, then "The swap failed," is written.*/

vector < vector <int> > new_hcount_board(Board& brd);
/*takes on input the game Board and returns the
//hcount representation of the board*/

vector < vector <int> > new_vcount_board(Board& brd);
/*takes on input the game Board and returns the
//vcount representation of the board*/

int pairs_of_threes_hcount(vector < vector <int> > hcount_board);
/*takes on input the hcount_board
//and then counts the number of pairs
//in hcount_board.
//Returns the count*/
int pairs_of_threes_vcount(vector < vector <int> > vcount_board);
/*takes on input the vcount_board
//and then counts the number of pairs
//in vcount_board.
//Returns the count*/

Board shift_until_no_threes(Board& brd);
/*takes on input the game Board
//then shifts the game board until there
//are no threes left in the game board
//returns the game board*/

int main() {
	cout << "Welcome to the game Match3\n";

	int dimension, number;
	cout << "Give the dimension of the board: ";
	cin >> dimension;
	cout << endl;

	if (dimension <= 2)
	{
		//If dimension s too small, quits the program. Dimension must be greater than 3.
		cout << "Error: Dimension is too low, please input a number greater or equal to 3." << endl;
		exit(1);
	}

	cout << "Give the number of different items: ";
	cin >> number;
	cout << endl;
	if (number < 2) {
		cout << "Error: Number is too low, please input a number greater or equal to 3." << endl;
		exit(1);
	}

	cout << "Generating a " << dimension << "-by-" << dimension << " board with " << number << " different items...\n";

	Board bd_1 = Board(dimension, number);
	Board bd_2 = bd_1;

	cout << "The Board: " << endl;
	cout << bd_1;

	string user_input1, user_input2;
	int shift_count = 0, hcount_count = 0, vcount_count = 0, user_score = 0, round_count = 0;
	char answer = 'y';

	cout << "Give the level of player one (-1 for interactive) : ";
	cin >> user_input1;
	cout << "Give the level of player two(-1 for interactive) : ";
	cin >> user_input2;

	string name_one = "Player_1";
	string name_two = "Player_2";

	int player_level_one = atoi(user_input1.c_str());
	int player_level_two = atoi(user_input2.c_str());

	Player player_one = Player(&bd_1, name_one, player_level_one);
	Player player_two = Player(&bd_1, name_two, player_level_two);
	cout << player_one;

	cout << player_two;


	
	while (answer == 'y')
	{
		cout << "The game starts..." << endl;
		cout << "Player one's turn..." << endl;
		player_one.play();
		cout << "Player two's turn..." << endl;
		player_two.play();
		cout << "Would you like to continue? ";
		cin >> answer;
	}

	if (player_one.get_score() > player_two.get_score()) {
		cout << "Player_one wins with " << player_one.get_score() << " over " << player_two.get_score() << ".";
	}
	else if (player_two.get_score() > player_one.get_score()) {
		cout << "Player_two wins with " << player_two.get_score() << " over " << player_one.get_score() << ".";
	}
	else {
		cout << "The game is a draw: " << player_two.get_score() << "-" << player_one.get_score() << ".";
	}

	return 0;
}

vector < vector <int> > new_hcount_board(Board& brd) {
	vector< vector <int> > hcount_board(brd.dimension(), vector<int>(brd.dimension(), 0));
	//getting vcounts of bd.board
	for (int r = 0; r < brd.dimension(); ++r)
	{
		for (int c = 0; c < brd.dimension(); ++c)
		{
			hcount_board[r][c] = brd.hcount(r, c);
		}
	}
	return hcount_board;
}

vector < vector <int> > new_vcount_board(Board& brd) {
	vector< vector <int> > vcount_board(brd.dimension(), vector<int>(brd.dimension(), 0));
	//getting vcounts of bd.board
	for (int r = 0; r < brd.dimension(); ++r)
	{
		for (int c = 0; c < brd.dimension(); ++c)
		{
			vcount_board[r][c] = brd.vcount(r, c);
		}
	}
	return vcount_board;
}

int pairs_of_threes_hcount(vector < vector <int> > hcount_board) {
	int hcount_pair_counter = 0;
	for (int r = 0; r < unsigned(hcount_board.size()); ++r)
	{
		for (int c = 0; c < hcount_board.size(); ++c)
		{
			if (hcount_board[r][c] >= 3)
			{
				hcount_pair_counter++;
			}
		}
	}
	return hcount_pair_counter;
}

int pairs_of_threes_vcount(vector < vector <int> > vcount_board)
{
	int vcount_pair_counter = 0;
	for (int r = 0; r < vcount_board.size(); ++r)
	{
		for (int c = 0; c < vcount_board.size(); ++c)
		{
			if (vcount_board[r][c] >= 3)
			{
				vcount_pair_counter++;
			}
		}
	}
	return vcount_pair_counter;
}

Board shift_until_no_threes(Board& brd) {
	vector < vector <int> > hcount_board = new_hcount_board(brd);
	vector < vector <int> > vcount_board = new_vcount_board(brd);
	int hpairs = pairs_of_threes_hcount(hcount_board);
	int vpairs = pairs_of_threes_vcount(vcount_board);

	while (hpairs != 0 || vpairs != 0)
	{
		for (int r = 0; r < brd.dimension(); ++r)
		{
			for (int c = 0; c < brd.dimension(); ++c)
			{
				if (hcount_board[r][c] >= 3 || vcount_board[r][c] >= 3)
				{
					brd.shift(r, c);

					hcount_board = new_hcount_board(brd);
					vcount_board = new_vcount_board(brd);

					hpairs = pairs_of_threes_hcount(hcount_board);

					vpairs = pairs_of_threes_vcount(vcount_board);

				}
			}
		}
	}

	return brd;
}