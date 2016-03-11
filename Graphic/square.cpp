/**
	Author: Ahsan Zaman
 **/
 #include "square.h"

Square::Square(int t){if(check_type(t)) type = t;}

Square::~Square(){};

void Square::set_val(int t){type = t;}

int Square::val(){return type;}

bool Square::check_type(int t){
	if((t>=0 && t<=9) || t==O || t==X) return true;
	else return false;
}