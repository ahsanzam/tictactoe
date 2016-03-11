/**
	Author: Ahsan Zaman
 **/
const int X = -1;
const int O = -2;

class Square
{
public: 
	Square(int t);
	~Square();
	void set_val(int t);
	int val();
private: 
	bool check_type(int t);
	int type;
};