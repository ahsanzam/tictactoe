/**
	Author: Ahsan Zaman
 **/
#include <iostream> 
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>

using namespace std; 

const int X = -1;
const int O = -2;

class Square
{
	public: 
		Square(int t){if(check_type(t)) type = t;}
		~Square(){};
		void print(){
			if(type == X) cout << "X | ";
			else if(type == O) cout << "O | ";
			else cout << type << " | ";
		}
		void set_val(int t){type = t;}
		int val(){return type;}
	private: 
		bool check_type(int t){
			if((t>=0 && t<=9) || t==O || t==X) return true;
			else return false;
		}
		int type;
};

void show_board(vector<Square*> &s);
vector<Square*> set_up_board();
bool play_game_mfirst(vector<Square*> &s);
bool play_game_pfirst(vector<Square*> &s);
int move_gen(vector<Square*> &s);
int move_gen(vector<Square*> &s, int &state);
int check_win(vector<Square*> &s);
bool is_error(int input, vector<Square*> &s);
bool is_number(string input);

int main(){
	string order;
	vector<Square*> squares = set_up_board();
	show_board(squares);
	cout << "Would you like to go first? Enter y/n: " ;
	getline(cin, order);
	while(order!="y" && order!="n"){
		cout << "Enter y or n: ";
		getline(cin, order);
	}
	if(order=="y"){
		if(play_game_pfirst(squares)) 
			cout << "Yikes, you've lost!\n" ;
		else if(check_win(squares)==1)
			cout << "Tie." << endl;
		else
			cout << "Congratulations, you've won!\n" ;
	}
	else if(order=="n"){
		if(play_game_mfirst(squares)) 
			cout << "Yikes, you've lost!\n" ;
		else if(check_win(squares)==1)
			cout << "Tie." << endl;
		else
			cout << "Congratulations, you've won!\n" ;
	}
	for(int i=1; i<squares.size(); i++){
		delete squares[i];
	}
	return 0;
}

//prints out values for the board
void show_board(vector<Square*> &s){
	for(int i=1; i<10; i++){
		s[i]->print();
		if(!(i%3)){cout << "\n__|___|___|\n";}
	}
}

//pushes in initial values for squares
vector<Square*> set_up_board(){
	vector<Square*> v;
	v.push_back(NULL);
	for(int i=1; i<10; i++){
		Square *s = new Square(i);
		v.push_back(s);
	}
	return v;
}

//enters game loop with player moving first
bool play_game_pfirst(vector<Square*> &s)
{
	int state = 1;
	bool at_end = false;
	while(!at_end){
		string input;
		int index;
		bool error = true; 
		cout << "Pick a square: " ;
		//check for error in input
		while(error){
			getline(cin, input);
			if(!(is_number(input))) error = true;
			else if(is_error(atoi(input.c_str()), s)) error = true;
			else{ 
				error = false;
				index = atoi(input.c_str());
			} 
			if(error && input!="") cout << "Try again! " ;
		}
		s[index]->set_val(X);
		show_board(s);
		if(check_win(s) != 0) at_end = true;
		state++;

		//machine's turn
		if(!at_end){
			cout << "My turn!\n";
			if(state==2) index = move_gen(s, state);
			else index = move_gen(s);
			cout << "I pick square "<< index << endl;
			s[index]->set_val(O);
			show_board(s);
			if(check_win(s) != 0) 
				at_end = true;
		}
		state++;
	}
	if(check_win(s)==O) return true;
	else return false;
}
//enters game loop with machine moving first
bool play_game_mfirst(vector<Square*> &s)
{
	int state = 1;
	bool at_end = false;
	while(!at_end){
		string input;
		int index;
		bool error = true; 
		//machine's turn
		cout << "My turn!\n";
		if(state==1) index = move_gen(s, state);
		else index = move_gen(s);
		cout << "I pick square "<< index << endl;
		s[index]->set_val(O);
		show_board(s);
		if(check_win(s) != 0) 
			at_end = true;
		state++; 

		//player's turn
		if(!at_end){
			cout << "Your turn. Pick a square: " ;
			//check for error in input
			while(error){
				getline(cin, input);
				if(!(is_number(input))) error = true;
				else if(is_error(atoi(input.c_str()), s)) error = true;
				else{
					error = false;
					index = atoi(input.c_str());
				} 
				if(error && input!="") cout << "Try again! " ;
			}
			s[index]->set_val(X);
			show_board(s);
			if(check_win(s) != 0) at_end = true;
		}
		state++;
	}
	if(check_win(s)==O) return true;
	else return false;
}
//allows computer to generate moves for first move
int move_gen(vector<Square*> &s, int &state)
{
	if(state==1) return 1;
	else if(s[5]->val()!=X) return 5;
	else return 1;
}
//allows computer to generate moves for move after first
int move_gen(vector<Square*> &s){
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
	else{
		for(int i=0; i<10; i++){if(s[i]->val()>0) return i;}
	}
}

//checks for end state
int check_win(vector<Square*> &s)
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
bool is_error(int input, vector<Square*> &s)
{
	if(input>9 || input<1) return true;
	else if(s[input]->val()==X || s[input]->val()==O) return true;
	return false;
}

//checks whether an input string is a number 
bool is_number(string input)
{
	for(int i=0; i<input.size(); i++){
		if(input[i] < '1' || input[i]>'9') return false;
	}
	return true; 
}