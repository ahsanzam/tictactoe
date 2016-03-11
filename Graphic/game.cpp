/**
	Author: Ahsan Zaman
 **/
#include "game.h"

Game::Game(){
	set_up_board();
	win = false;
}
Game::~Game(){
	for(int i=1; i<10; i++)
		delete s[i];
}
void Game::player_move(int i){
	if( !is_error(i) )
		s[i]->set_val(X);
}
int Game::move(){
	int i = move_gen();
	s[i]->set_val(O);
	return i;
}

//pushes in initial values for squares
void Game::set_up_board(){
	s.push_back(NULL);
	for(int i=1; i<10; i++){
		Square *c = new Square(i);
		s.push_back(c);
	}
}

//allows computer to generate moves 
int Game::move_gen(){
	if(s[1]->val()==s[2]->val() && s[3]->val()>0) return 3; //1
	if(s[4]->val()==s[5]->val() && s[6]->val()>0) return 6; //2
	if(s[7]->val()==s[8]->val() && s[9]->val()>0) return 9; //3
	if(s[1]->val()==s[5]->val() && s[9]->val()>0) return 9; //4
	if(s[3]->val()==s[5]->val() && s[7]->val()>0) return 7; //5
	if(s[2]->val()==s[5]->val() && s[8]->val()>0) return 8; //6
	if(s[7]->val()==s[5]->val() && s[3]->val()>0) return 3; //7
	if(s[8]->val()==s[5]->val() && s[2]->val()>0) return 2; //8
	if(s[6]->val()==s[5]->val() && s[4]->val()>0) return 4; //9
	if(s[9]->val()==s[5]->val() && s[1]->val()>0) return 1; //10
	if(s[3]->val()==s[2]->val() && s[1]->val()>0) return 1; //11
	if(s[9]->val()==s[8]->val() && s[7]->val()>0) return 7; //12
	if(s[1]->val()==s[9]->val() && s[5]->val()>0) return 5; //13
	if(s[3]->val()==s[7]->val() && s[5]->val()>0) return 5; //14
	if(s[1]->val()==s[3]->val() && s[2]->val()>0) return 2; //15
	if(s[4]->val()==s[6]->val() && s[5]->val()>0) return 5; //16
	if(s[7]->val()==s[9]->val() && s[8]->val()>0) return 8; //17
	if(s[1]->val()==s[7]->val() && s[4]->val()>0) return 4; //18
	if(s[2]->val()==s[8]->val() && s[5]->val()>0) return 5; //19
	if(s[3]->val()==s[9]->val() && s[6]->val()>0) return 6; //20
	else
		for(unsigned int i=1; i<10; i++) if(s[i]->val()>0) 
			return i;
	std::cout << "ERROR!" << std::endl;
	return -1; //error code
}

//checks for end state
int Game::check_win()
{
	if(s[1]->val()==s[2]->val()  && s[2]->val()==s[3]->val()) return s[3]->val();
	else if(s[4]->val()==s[5]->val()  && s[5]->val()==s[6]->val()) return s[6]->val();
	else if(s[7]->val()==s[8]->val()  && s[8]->val()==s[9]->val()) return s[9]->val();
	else if(s[1]->val()==s[4]->val()  && s[4]->val()==s[7]->val()) return s[7]->val();
	else if(s[2]->val()==s[5]->val()  && s[5]->val()==s[8]->val()) return s[8]->val();
	else if(s[3]->val()==s[6]->val()  && s[6]->val()==s[9]->val()) return s[9]->val();
	else if(s[1]->val()==s[5]->val()  && s[5]->val()==s[9]->val()) return s[9]->val();
	else if(s[3]->val()==s[5]->val()  && s[5]->val()==s[7]->val()) return s[7]->val();
	else{
		for(int i=1; i<10; i++){
			if(s[i]->val()!=X && s[i]->val()!=O) return 0;
		}
		return 1;
	}
}

//checks for error in input
bool Game::is_error(int input)
{
	if(s[input]->val()==X || s[input]->val()==O) return true;
	return false;
}
