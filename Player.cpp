// MCS 360 Project 5 by <Gierach, Thomas> and <Yee, Justin>
#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(Board* bd, string player, int lvl = 0) : board(bd), name(player), level(lvl) {
	score = 0;
	shift_count = 0;
}
/*	Parameters:
	1. The pointer to the board that is shared by all players in the game.
	2. The name of the player is a string.
	3. The level of the player has default value zero. Other possible values are-1, +1, and +2.
	   The level determines the behavior of play() and is explained below.
	The constructor initializes the score of the player to zero.
*/
int Player::get_level() {
	return level;
}
int Player::get_score() {
	return score;
}
void Player::play() {
	this->shift_count = 0;
	*this->board = shift_until_no_threes(*this->board, true);

	if (this->get_level() == -1) {
		this->neg_one();
	}
	else if (this->get_level() == 0) {
		this->zero();
	}
	else if (this->get_level() == 1) {
		this->one();
	}
	else if (this->get_level() == 2) {
		this->two();
	}
}
/*	-First shift away all matchings of 3 (and more), incrementing the score of the player
	 with each step of the shift loop. Then a swap will be attempted.
	-If the swap is successful, the score is
	 incremented and the shift loop will run again.
	-To implement the level +2 correctly, the play() method must try several swaps
	 and reset the board before trying the next swap.*/


ostream& operator<<(ostream& os, Player& player) {
	os << "Player name: " << player.name << " level: " << player.get_level() << " score: " << player.get_score() << endl;
	os << *player.board << endl;
	//operator<<(os, *player.board);
	//os << endl;
	return os;
}

int Player::get_shift_count() {
	return shift_count;
}
void Player::neg_one() {
	vector < vector <int> > hcount_board;
	vector < vector <int> > vcount_board;
	string answer = "y";
	int hcount_count = 0, vcount_count = 0;
	int row_index, col_index;
	bool swap;

	while (answer == "y") {
		cout << "total number of shifts: " << this->get_shift_count() << endl;

		cout << "give a row index: ";
		cin >> row_index;
		cout << endl;

		cout << "give a column index: ";
		cin >> col_index;
		cout << endl;

		swap = this->board->swap(row_index, col_index);

		if (swap == true) {
			this->board->shift(row_index, col_index);
			this->shift_count++;
			this->score++;
			cout << "total number of shifts: " << this->get_shift_count() << endl;
			cout << "the current board:\n" << *this->board << endl;
			cout << this->name << " at level " << this->get_level() << " has score " << this->get_score() << endl;
			*this->board = shift_until_no_threes(*this->board, true);
		}
		else {
			cout << "The swap failed." << endl;
			cout << "the current board:\n" << *this->board << endl;
			cout << "total number of shifts: " << this->get_shift_count() << endl;
			cout << this->name << " at level " << this->get_level() << " has score " << this->get_score() << endl;
		}

		hcount_board = new_hcount_board(*this->board);
		vcount_board = new_vcount_board(*this->board);
		int hpairs = pairs_of_threes_hcount(hcount_board);
		int vpairs = pairs_of_threes_vcount(vcount_board);

		cout << "total number of shifts: " << this->get_shift_count() << endl;
		cout << "the current board:\n" << *this->board << endl;
		cout << "total number of shifts: " << this->get_shift_count() << endl;
		cout << this->name << " at level " << this->get_level() << " has score " << this->get_score() << endl;
		cout << "Continue (y/n): ";
		cin >> answer;
		cout << endl;
	}
}
//plays if level == -1
//The player prompts the user for a rowand column index.
void Player::zero() {
	int r, c;
	bool swap = false;
	string answer = "y";
	vector < vector <int> > hcount_board;
	vector < vector <int> > vcount_board;
	int d = this->board->dimension();
	while (answer == "y") {
		r = rand() % d;
		c = rand() % d;
		swap = this->board->swap(r, c);
		if (swap == true) {
			this->board->shift(r, c);
			this->shift_count++;
			this->score++;
			cout << "total number of shifts: " << this->get_shift_count() << endl;
			cout << "the current board:\n" << *this->board << endl;
			//cout << "total number of shifts: " << this->get_shift_count() << endl;
			cout << this->name << " at level " << this->get_level() << " has score " << this->get_score() << endl;
			*this->board = shift_until_no_threes(*this->board, true);
		}
		else {
			cout << "The swap failed." << endl;
			cout << "the current board:\n" << *this->board << endl;
			cout << "total number of shifts: " << this->get_shift_count() << endl;
			cout << this->name << " at level " << this->get_level() << " has score " << this->get_score() << endl;
		}
		cout << "total number of shifts: " << this->get_shift_count() << endl;
		cout << this->name << " at level " << this->get_level() << " has score " << this->get_score();
		cout << endl;
		cout << "Continue (y/n): ";
		cin >> answer;
		cout << endl;
	}

}
//plays if level == 0
//The player generates a random value for the row and column index.
void Player::one() {
	int r_swap = 0, c_swap = 0;
	bool swap = false;
	string answer = "y";
	vector < vector <int> > hcount_board;
	vector < vector <int> > vcount_board;
	int d = this->board->dimension();
	while (answer == "y")
	{
		for (int r = 0; r < d; ++r)
		{
			for (int c = 0; c < d; ++c)
			{
				swap = this->board->swap(r, c);

				if (swap == true)
				{
					//cout << "swap successful" << endl;
					r_swap = r;
					c_swap = c;
					break;
				}
				else
				{
					//cout << "Swap failed at: (" << r << ", " << c << ")" << endl;
					
				}
			}
			if (swap == true)
			{
				break;
			}
		}

		if (swap == true)
		{
			//cout << "swap successful" << endl;
			//cout << "shifting board" << endl;
			this->board->shift(r_swap, c_swap);
			this->shift_count++;
			this->score++;
			cout << "total number of shifts: " << this->get_shift_count() << endl;
			cout << "the current board:\n" << *this->board << endl;
			//cout << "total number of shifts: " << this->get_shift_count() << endl;
			cout << this->name << " at level " << this->get_level() << " has score " << this->get_score() << endl;
			*this->board = shift_until_no_threes(*this->board, true);
		}
		else
		{
			cout << "The swap failed." << endl;
			cout << "the current board:\n" << *this->board << endl;
			cout << "total number of shifts: " << this->get_shift_count() << endl;
			cout << this->name << " at level " << this->get_level() << " has score " << this->get_score() << endl;
		}
		//cout << "outside the if-else condition: " << endl;
		cout << "total number of shifts: " << this->get_shift_count() << endl;
		cout << "the current board:\n" << *this->board << endl;
		//cout << "total number of shifts: " << this->get_shift_count() << endl;
		cout << this->name << " at level " << this->get_level() << " has score " << this->get_score() << endl;
		cout << "Continue (y/n): ";
		cin >> answer;
		cout << endl;
	}
}
//plays if level == 1
//The player uses the first value of the row and column index so a swap gives a matching of 3 or more.
void Player::two() {
	cout << "in level two" << endl;
	int high = 0, current_high = 0, current_r_high = 0, r_high = 0, current_c_high = 0, c_high = 0, h_pairs = 0, v_pairs = 0;
	bool swap_main = false;
	bool test_swap = false;

	string answer = "y";
	vector < vector <int> > hcount_board;
	vector < vector <int> > vcount_board;
	int d = this->board->dimension();
	Board* brd = this->board;
	while (answer == "y")
	{
		for (int r = 0; r < d; ++r)
		{
			for (int c = 0; c < d; ++c)
			{
				test_swap = brd->swap(r, c);
				if (test_swap == true)
				{
					hcount_board = this->new_hcount_board(*brd);
					vcount_board = this->new_vcount_board(*brd);
					h_pairs = this->pairs_of_threes_hcount(hcount_board);
					//cout << "H_pairs: " << h_pairs << endl;
					v_pairs = this->pairs_of_threes_vcount(vcount_board);
					//cout << "V_pairs: " << v_pairs << endl;
					current_r_high = r;
					//cout << "current_r_high: " << current_r_high << endl;
					current_c_high = c;
					//cout << "current_c_high: " << current_c_high << endl;
					if (h_pairs > v_pairs) {
						//cout << "in h_pairs > v_pairs loop" << endl;
						current_high = h_pairs;
						//cout << "current_high: " << current_high << endl;
					}
					else {
						//cout << "in v_pairs > h_pairs condition" << endl;
						current_high = v_pairs;
						//cout << "current_high: " << current_high << endl;
					}
					if (current_high > high) {
						//cout << "current high > high condition" << endl;
						high = current_high;
						//cout << "high: " << high << endl;
						r_high = r;
						//cout << "r_high: " << r_high << endl;
						c_high = c;
						//cout << "c_high: " << c_high << endl;
					}
					//cout << "resetting the board: " << endl;
					brd = this->board;
				}
			}
		}

		swap_main = this->board->swap(r_high, c_high);
		cout << swap_main << endl;
		if (swap_main == true) {
			this->board->shift(r_high, c_high);
			this->shift_count++;
			this->score++;
			cout << "total number of shifts: " << this->get_shift_count() << endl;
			cout << "the current board:\n" << *this->board << endl;
			//cout << "total number of shifts: " << this->get_shift_count() << endl;
			cout << this->name << " at level " << this->get_level() << " has score " << this->get_score() << endl;
			*this->board = shift_until_no_threes(*this->board, true);
		}
		else {
			cout << "The swap failed." << endl;
			cout << "the current board:\n" << *this->board << endl;
			cout << "total number of shifts: " << this->get_shift_count() << endl;
			cout << this->name << " at level " << this->get_level() << " has score " << this->get_score() << endl;
		}
		cout << "total number of shifts: " << this->get_shift_count() << endl;
		cout << "the current board:\n" << *this->board << endl;
		//cout << "total number of shifts: " << this->get_shift_count() << endl;
		cout << this->name << " at level " << this->get_level() << " has score " << this->get_score() << endl;
		cout << "Continue (y/n): ";
		cin >> answer;
		cout << endl;
	}
}
//plays if level == 2
//The player uses the best value of the row and column index so a swap gives the highest matching.
//plays if level == 2
vector < vector <int> > Player::new_hcount_board(Board& brd) {
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

vector < vector <int> > Player::new_vcount_board(Board& brd) {
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

int Player::pairs_of_threes_hcount(vector < vector <int> > hcount_board) {
	int hcount_pair_counter = 0;
	for (int r = 0; r < hcount_board.size(); ++r)
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

int Player::pairs_of_threes_vcount(vector < vector <int> > vcount_board)
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

Board Player::shift_until_no_threes(Board& brd, bool verbose) {
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
					this->score++;
					this->shift_count++;
					hcount_board = new_hcount_board(brd);
					vcount_board = new_vcount_board(brd);
					if (verbose == true) {
						cout << "The board after shift " << this->get_shift_count() << endl;
						cout << *this->board << endl;
						//cout << brd << endl;
					}
					hpairs = pairs_of_threes_hcount(hcount_board);
					vpairs = pairs_of_threes_vcount(vcount_board);

				}
			}
		}
	}

	return brd;
}
