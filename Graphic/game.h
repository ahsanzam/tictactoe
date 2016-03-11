/**
	Author: Ahsan Zaman
 **/
#include <iostream> 
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <square.h>

extern const int X;
extern const int O;

class Game
{
public:
	Game();
	~Game();
	void player_move(int i);
	int move();
	bool is_error(int input);
	int check_win();

private:
	void set_up_board();
	bool play_game_mfirst();
	bool play_game_pfirst();
	int move_gen();

	std::vector<Square*> s;
	bool win;
};
