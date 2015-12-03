
#include "stdafx.h"
#include "gomoku.h"

using namespace std;

//Gomoku Class with custom dimensions and win conditions for extra credit
Gomoku::Gomoku(int size, int win){
	x = size;
	stringlength = defaultstrsize;
	this->win = win;
	xturn = true;

	for (int i = 0; i < x*x; ++i){
		v.push_back(" ");
	}

	xturns = "Player B:";
	oturns = "Player W:";
	player1 = "Player B";
	player2 = "Player W";

	type = "Gomoku";

	ifstream old;
	old.open(type);

	if (old.is_open()){
		string line;
		getline(old, line);
		if (line == "Gomoku"){
			int tempX;
			int tempWin;

			getline(old, line);
			istringstream sIn(line);
			sIn >> tempX;

			getline(old, line);
			istringstream sInAgain(line);
			sInAgain >> tempWin;

			string playerAns;
			while (playerAns != "y" && playerAns != "n"){
				cout << "There is currently a saved game of game board size " << tempX - 2 << "x" << tempX - 2 << " with a win condition of " << tempWin << " in a row" << endl;
				cout << "Would you like to continue this saved game? (y = continue, n = new game with your desired conditions)" << endl;
				cin >> playerAns;
			}

			if (playerAns == "y"){
				v.clear();
				getline(old, line);
				istringstream sIn(line);
				sIn >> tcount;

				x = tempX;
				this->win = tempWin;

				if (tcount % 2 == 0){
					xturn = true;
				}
				else{
					xturn = false;
				}
				

				while (getline(old, line)){
					string temp;
					istringstream sIn(line);
					sIn >> temp;
					if (temp == "B" || temp == "W"){
						v.push_back(temp);
					}
					else{
						v.push_back(" ");
					}
				}
			}
		}
	}
}

//Default constructor
Gomoku::Gomoku(){
	x = defaultsize;
	win = defaultwin;
	stringlength = defaultstrsize;
	xturn = true;

	for (int i = 0; i < x*x; ++i){
		v.push_back(" ");
	}

	xturns = "Player B:";
	oturns = "Player W:";
	player1 = "Player B";
	player2 = "Player W";

	type = "Gomoku";

	ifstream old;
	old.open(type);

	if (old.is_open()){
		string line;
		getline(old, line);
		if (line == "Gomoku"){
			int tempX;
			int tempWin;

			getline(old, line);
			istringstream sIn(line);
			sIn >> tempX;

			getline(old, line);
			istringstream sInAgain(line);
			sInAgain >> tempWin;

			string playerAns;
			while (playerAns != "y" && playerAns != "n"){
				cout << "There is currently a saved game of game board size " << tempX - 2 << "x" << tempX - 2 << " with a win condition of " << tempWin << " in a row" << endl;
				cout << "Would you like to continue this saved game? (y = continue, n = new game with your desired conditions)" << endl;
				cin >> playerAns;
			}

			if (playerAns == "y"){
				v.clear();
				getline(old, line);
				istringstream sIn(line);
				sIn >> tcount;

				x = tempX;
				this->win = tempWin;

				if (tcount % 2 == 0){
					xturn = true;
				}
				else{
					xturn = false;
				}

				while (getline(old, line)){
					string temp;
					istringstream sIn(line);
					sIn >> temp;
					if (temp == "B" || temp == "W"){
						v.push_back(temp);
					}
					else{
						v.push_back(" ");
					}
				}
			}
		}
	}

}
//Overloaded operator builds the board using nested for loops to create a two dimensional array,
//also works for larger maximum string lengths
ostream & operator<< (ostream &o, const Gomoku &t){
	for (int j = t.x - 1;
 j >= 0; --j){
		o << j;
		if (j <= singledig){
			o << " ";
		}
		for (int i = 0; i < t.x; ++i){
			for (unsigned int k = 0; k < (t.stringlength - t.v[t.x*j + i].size() + 1); ++k){   
				o << " ";
			}
			o << " " << t.v[t.x * j + i];
		}
		o << endl;
	}
	//This part does the bottom row
	o << "  ";
	for (int i = 0; i < t.x; ++i){
		for (int k = 0; k < (t.stringlength); ++k){  //More tricky formatting to make sure it alligns properly with double digit coordinates.
			o << " ";		
		}
		if (i <= singledig){
			o << " ";
		}
		o << i;
	}
	o << endl;
	return o;
}

//Prints the board
void Gomoku::print(){
	cout << *this << endl;
}

//check pieces around last dropped piece to see if that player has won using methods created to check each direction.
const bool Gomoku::done(){
	string letter = v[lastpiece];
	if (checkdiag1(lastpiece, letter)>=win || checkdiag2(lastpiece, letter)>=win || checkhor(lastpiece, letter)>=win || checkvert(lastpiece, letter)>=win){
		return true;
	}

	return false;
}

//Horizontal win condition checker
int Gomoku::checkhor(int i, string letter){
	bool check = true;
	int left = 0;
	int right = 0;
	int position = i;
	while (check){  //Checks to the right of the last piece placed
		if ((position+1)%x != x-1 && v[position + 1] == letter){
			++right;
			++position;
		}
		else{
			check = false;
		}
	}
	position = i;
	check = true;
	while (check){ //Checks to the left of the last piece placed
		if ((position - 1) % x != 0 && v[position - 1] == letter){
			++left;
			--position;
		}
		else{
			check = false;
		}
	}

	return left + right + 1; //Combines both directions to see if we have the right amount in a row.
}

//Vertical win condition checker
int Gomoku::checkvert(int i, string letter){
	bool check = true;
	int top = 0;
	int bottom = 0;
	int position = i;
	while (check){  //Checks abovoe
		if ((position + x) < x*x - x && v[position + x] == letter){
			++top;
			position = position + x;
		}
		else{
			check = false;
		}
	}
	position = i;
	check = true;
	while (check){ //Checks below
		if ((position - x) > x && v[position - x] == letter){
			++bottom;
			position = position - x;
		}
		else{
			check = false;
		}
	}

	return top + bottom + 1; //adds them up
}

//First diagonal win condition checker
int Gomoku::checkdiag1(int i, string letter){
	bool check = true;
	int top = 0;
	int bottom = 0;
	int position = i;
	while (check){ //Checks to the top right
		if ((position + x) < x*x - x && (position + 1) % x != x - 1 && v[position + x + 1] == letter){
			++top;
			position = position + x + 1;
		}
		else{
			check = false;
		}
	}
	position = i;
	check = true;
	while (check){//Checks to the bottom left
		if ((position - x) > x && (position - 1) % x != 0 && v[position - x - 1] == letter){
			++bottom;
			position = position - x - 1;
		}
		else{
			check = false;
		}
	}

	return top + bottom + 1; //Combine
}

//Second diagonal win condition checker
int Gomoku::checkdiag2(int i, string letter){
	string letter2;
	bool check = true;
	int top = 0;
	int bottom = 0;
	int position = i;
	while (check){ //Checks to the Top Left
		if ((position + x) < x*x - x && (position - 1) % x != 0 && v[position + x - 1] == letter){
			++top;
			position = position + x - 1;
		}
		else{
			check = false;
		}
	}
	position = i;
	check = true;
	while (check){ //Checks to the bottom right
		if ((position - x) > x && (position + 1) % x != x - 1 && v[position - x + 1] == letter){
			++bottom;
			position = position - x + 1;
		}
		else{
			check = false;
		}
	}

	return top + bottom + 1; //combine
}

//horizontal draw condition checker
int Gomoku::dcheckhor(int i, string letter){
	bool check = true;
	int left = 0;
	int right = 0;
	int position = i;
	while (check){//check to the right
		if ((position + 1) % x != x - 1 && (v[position + 1] == letter || v[position + 1] == " ")){
			++right;
			++position;
		}
		else{
			check = false;
		}
	}
	position = i;
	check = true;
	while (check){//check to the left
		if ((position - 1) % x != 0 && (v[position - 1] == letter || v[position - 1] == " ")){
			++left;
			--position;
		}
		else{
			check = false;
		}
	}

	return left + right + 1;//combine
}

//Vertical draw condition checker
int Gomoku::dcheckvert(int i, string letter){
	bool check = true;
	int top = 0;
	int bottom = 0;
	int position = i;
	while (check){//check above
		if ((position + x) < x*x - x && (v[position + x] == letter || v[position + x] == " ")){
			++top;
			position = position + x;
		}
		else{
			check = false;
		}
	}
	position = i;
	check = true;
	while (check){//check below
		if ((position - x) > x && (v[position - x] == letter || v[position - x] == " ")){
			++bottom;
			position = position - x;
		}
		else{
			check = false;
		}
	}
	return top + bottom + 1; //combine
}

//First diagonal draw condition checker
int Gomoku::dcheckdiag1(int i, string letter){
	bool check = true;
	int top = 0;
	int bottom = 0;
	int position = i;
	while (check){//checks to the top right
		if ((position + x) < x*x - x && (position + 1) % x != x - 1 && (v[position + x + 1] == letter || v[position + x + 1] == " ")){
			++top;
			position = position + x + 1;
		}
		else{
			check = false;
		}
	}
	position = i;
	check = true;
	while (check){ //checks to the bottom left
		if ((position - x) > x && (position - 1) % x != 0 && (v[position - x - 1] == letter || v[position - x - 1] == " ")){
			++bottom;
			position = position - x - 1;
		}
		else{
			check = false;
		}
	}

	return top + bottom + 1; //combines
}

//Second diagonal draw condition checker
int Gomoku::dcheckdiag2(int i, string letter){
	string letter2;
	bool check = true;
	int top = 0;
	int bottom = 0;
	int position = i;
	while (check){ //Checks to the top left
		if ((position + x) < x*x - x && (position - 1) % x != 0 && (v[position + x - 1] == letter || v[position + x - 1] == " ")){
			++top;
			position = position + x - 1;
		}
		else{
			check = false;
		}
	}
	position = i;
	check = true;
	while (check){ //Checks to the bottom right
		if ((position - x) > x && (position + 1) % x != x - 1 && (v[position - x + 1] == letter || v[position - x + 1] == " ")){
			++bottom;
			position = position - x + 1;
		}
		else{
			check = false;
		}
	}

	return top + bottom + 1; //combines
}

//Checks to see if the game is over via tie. 
const bool Gomoku::draw(){
	bool emptys = false;
	bool canwin = false;
	for (int i = validstart; i < x - 1; ++i){ //Checks every pieve
		for (int j = validstart; j < x - 1; ++j){
			if (v[x * j + i] == " "){
				emptys = true;
				//Sees if it can possibly win in every direction
				int hor = max(dcheckhor(x*j + i, "W") , dcheckhor(x*j + i, "B"));
				int vert = max(dcheckvert(x*j + i, "W"), dcheckvert(x*j + i, "B"));
				int diag1 = max(dcheckdiag1(x*j + i, "W"), dcheckdiag1(x*j + i, "B"));
				int diag2 = max(dcheckdiag2(x*j + i, "W"), dcheckdiag2(x*j + i, "B"));

				if (max(hor, vert)  >= win || max(diag1, diag2)  >= win){
					canwin = true;
				}
				
			}
		}
	}

	if (canwin || done()){
		return false;
	}
	else{
		return true;
	}
}

//Manages the turns between the two players
const int Gomoku::turn(){
	char little;
	char big;
	//Initialize variables based on whose turn it is.
	if (xturn){
		cout << "It is Player B's turn." << endl;
		little = 'b';
		big = 'B';
	}
	else{
		cout << "It is Player W's turn." << endl;
		little = 'w';
		big = 'W';
	}
	unsigned int i, j;
	//Start prompt function
	int valid = prompt(i, j);
	if (valid == quit){
		return quit;
	}
	//Set vector spot
	lastpiece = x*j + i;
	v[x * j + i] = big;
	//Print board
	cout << *this << endl << endl;
	//Show past turns based on player
	if (xturn){
		stringstream ss;
		cout << xturns << " " << i << ", " << j << endl;
		ss << xturns << " " << i << ", " << j << ';';
		xturns = ss.str();
	}
	else{
		stringstream ss;
		cout << oturns << " " << i << ", " << j << endl;;
		ss << oturns << " " << i << ", " << j << ';';
		oturns = ss.str();
	}
	tcount++;
	xturn = !xturn;
	return success;

}