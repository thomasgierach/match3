// MCS 360 Project 5 by <Gierach, Thomas> and <Yee, Justin>
#pragma once
#include "Board.h"

class Player {
private:
		string name;
		//represent the name of the player
		Board *board;
		//pointer to the board class
		int level;
		//determines the level of play with values: -1, +1, and +2
		int score;
		//the score of the player
		int shift_count;
		//the number of shifts for the current round
		void neg_one();
		//plays if level == -1
		//The player prompts the user for a rowand column index.
		void zero();
		//plays if level == 0
		//The player generates a random value for the rowand column index.
		void one();
		//plays if level == 1
		//The player uses the first value of the row and column index so a swap gives a matching of 3 or more.
		void two();
		//plays if level == 2
		//The player uses the best value of the row and column index so a swap gives the highest matching.
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
		Board shift_until_no_threes(Board& brd, bool verbose);
		/*takes on input the game Board
		//then shifts the game board until there
		//are no threes left in the game board
		//returns the game board*/
		int get_shift_count();
		/*returns the shift_count*/

public:
		Player(Board *bd, string player, int lvl);
		/*	Parameters:
			1. The pointer to the board that is shared by all players in the game.
			2. The name of the player is a string.
			3. The level of the player has default value zero. Other possible values are-1, +1, and +2.
			   The level determines the behavior of play() and is explained below.
			The constructor initializes the score of the player to zero.
		*/
		int get_level();
		/*returns the current value of the score of the player */
		int get_score();
		/*returns the level of the player.*/
		void play();
		/*	-First shift away all matchings of 3 (and more), incrementing the score of the player
			 with each step of the shift loop. Then a swap will be attempted. 
			-If the swap is successful, the score is
			 incremented and the shift loop will run again.
			-To implement the level +2 correctly, the play() method must try several swaps 
			 and reset the board before trying the next swap.*/
		friend ostream& operator<<(ostream& os, Player& player);
		/*prints the name of the player, its level, its score, and shows the board.*/
};