
#include "stdafx.h"
#include "tictactoe.h"

using namespace std;



//Default Constructor
TicTacToeGame::TicTacToeGame(){
	//Start by creating vector of chars, like board from lab1
	//Also initailize the private variables.
	x = 5;
	y = 5;
	xturn = true;
	xturns = "Player X:";
	oturns = "Player O:";
	player1 = "Player X";
	player2 = "Player O";
	tcount = 0;
	stringlength = 1;
	for (int i = 0; i < vectorsize; ++i){
		v.push_back(" ");
	}


	type = "TicTacToe";

	ifstream old;
	old.open(type);
	int i = 0;
	if (old.is_open()){
		string line;
		getline(old, line);
		if (line == "TicTacToe"){
			string playerAns;
			while (playerAns != "y" && playerAns != "n"){
				cout << "Would you like to continue a saved game? (y/n)" << endl;
				cin >> playerAns;
			}
			if (playerAns == "y"){
				getline(old, line);
				istringstream sIn(line);
				sIn >> tcount;
				if (tcount % 2 == 0){
					xturn = true;
				}
				else{
					xturn = false;
				}
				while (getline(old, line)){
					istringstream sIn(line);
					sIn >> v[i];
					i++;
				}
			}
		}
	}

}

//Checks for a win
const bool TicTacToeGame::done(){
	string empty = " ";
	//check solutions including top-right box, first column, row, and diagonal
	if (v[topleft] != empty && ((v[topleft] == v[middle] && v[topleft] == v[bottomright]) || (v[topleft] == v[middleleft] && v[topleft] == v[bottomleft]) || (v[topleft] == v[topmiddle] && v[topleft] == v[topright]))){
		return true;
	}
	//check solution involving top-middle, just second column
	if (v[topmiddle] != empty && (v[topmiddle] == v[middle] && v[topmiddle] == v[bottommiddle])){
		return true;
	}
	//check third column and second diagonal
	if (v[topright] != empty && ((v[topright] == v[middleright] && v[topright] == v[bottomright]) || (v[topright] == v[middle] && v[topright] == v[bottomleft]))){
		return true;
	}
	//check second row
	if (v[middleleft] != empty && (v[middleleft] == v[middle] && v[middleleft] == v[middleright])){
		return true;
	}
	//check third row
	if (v[bottomleft] != empty && (v[bottomleft] == v[bottommiddle] && v[bottomleft] == v[bottomright])){
		return true;
	}
	return false;
}

//Checks to see if the game is over via a tie.
const bool TicTacToeGame::draw(){
	bool emptys = false;
	//check board spots for empty spaces only on valid spots
	for (int i = validstart; i < totalrows - 1; ++i){
		for (int j = validstart; j < totalrows - 1; ++j){
			if (v[totalrows * j + i] == " "){
				emptys = true;
			}
		}
	}

	if (emptys || done()){
		return false;
	}
	else{
		return true;
	}
}


//Manages the turns between the two players
const int TicTacToeGame::turn(){
	char little;
	char big;
	//Initialize variables based on whose turn it is.
	if (xturn){
		cout << "It is Player X's turn." << endl;
		little = 'x';
		big = 'X';
	}
	else{
		cout << "It is Player O's turn." << endl;
		little = 'o';
		big = 'O';
	}
	unsigned int x, y;
	//Start prompt function
	int valid = prompt(x, y);
	if (valid == quit){
		return quit;
	}
	//Set vector spot
	v[totalrows * y + x] = little;
	//Print board
	cout << *this << endl << endl;
	//Show past turns based on player
	if (xturn){
		stringstream ss;
		cout << xturns << " " << x << ", " << y << endl;
		ss << xturns << " " << x << ", " << y << ';';
		xturns = ss.str();
	}
	else{
		stringstream ss;
		cout << oturns << " " << x << ", " << y << endl;;
		ss << oturns << " " << x << ", " << y << ';';
		oturns = ss.str();
	}
	tcount++;
	xturn = !xturn;
	return success;

}

//Prints out the board
void TicTacToeGame::print(){
	cout << *this << endl;
}

//Overloaded operator builds the board using nested for loops to create a two dimensional array
ostream & operator<< (ostream &o, const TicTacToeGame &t){
	for (int j = t.x - 1; j >= 0; --j){
		o << j;
		for (int i = 0; i < t.y; ++i){
			for (unsigned int k = 0; k < (t.stringlength - t.v[t.y*j + 1].size() + 1); ++k){
				o << " ";
			}
			o << t.v[t.y * j + i];					//Bunch of weird formatting lines to make it look nice.
		}
		o << endl;
	}
	o << " ";
	for (int i = 0; i < t.x; ++i){
		for (int k = 0; k < (t.stringlength); ++k){
			o << " ";
		}
		o << i;
	}
	o << endl;
	return o;
}





