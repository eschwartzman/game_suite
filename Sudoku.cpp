
#include "stdafx.h"
#include "sudoku.h"


using namespace std;

Sudoku::Sudoku(){
	//Start by creating vector of chars, like board from lab1
	//Also initailize the private variables.
	x = 9;
	for (int i = 0; i < x*x; ++i){
		v.push_back(" ");
		
	}

	type = "Sudoku";

	ifstream old;


	int count = 0;
	int spaceCount = 0;
	int lineCount = 0;
	//Open sudoku0file and put info in permanant numbers vector
	old.open("sudoku0");
	if (old.is_open()){
		string line;
		while (getline(old, line)){
			stringstream in(line);
			int temp;
			spaceCount = 0;
		
			while (in >> temp){
				if (temp == 0){
					v2.push_back(' ');
				}
				else{
					v2.push_back((temp + 48));
				}
				count++;
				spaceCount++;
			}

			if (spaceCount != spaceswanted){
				cout << "Error: Permanant sudoku0 File not formatted according to website. One or more lines do not 9 have valid inputs." << endl << endl;
				throw exception("Too many values");
			}
			lineCount++;
		}
		if (lineCount != spaceswanted){
			cout << "Error: Permanant sudoku0 File not formatted according to website. Need exactly 9 lines." << endl << endl;
			throw exception("Too many values");
		}
		//Enter permanant information into changible vector so it will draw.
		for (unsigned int i = 0; i < v.size(); ++i){
			v[i] = v2[i];
		}
	}
	else{
		cout << "Error: File 'sudoku0' not found." << endl;
		throw exception("No File");
	}
	old.close();
	//Open second file with newer save game info.
	old.open(type);
	count = 0;
	bool check;
	if (old.is_open()){
		string line;
		while (getline(old, line)){
			if (line == type){
				//Check to see if player wants to continue game
				string playerAns;
				while (playerAns != "y" && playerAns != "n"){
					cout << "Would you like to continue a saved game? (y/n)" << endl;
					cin >> playerAns;
				}
				check = (playerAns == "y");
			}

			if (!(line == "NO DATA" || line == type) && check){
				for (unsigned int i = 0; i < line.size(); ++i){
					if (count <= x*x){
						if (line.at(i) != ' '){
							if (v2[count] == ' '){
								if (line.at(i) == '0'){
									v[count] = ' ';
								}
								else{
									v[count] = line.at(i);
								}
								count++;
							}
							else{
								count++;
							}
						}


					}
					else{
						cout << "Error: File not formatted according to website." << endl;
						throw exception("Too many values");
					}
				}
			}
		}

	}



}

//Overloaded operator builds the board using nested for loops to create a two dimensional array
ostream & operator<< (ostream &o, const Sudoku &t){
	for (int j = t.x - 1; j >= 0; --j){
		o << j << "||";
		for (int i = 0; i < t.x; ++i){
			o << (t.v[t.x * j + i]) << "|";
			if (i % 3 == 2){
				o << "|";
			}
		}
		o << endl;
		if (j % 3 == 0){
			o << "=||=|=|=||=|=|=||=|=|=||" << endl;
		}
		else{
			o << "-||-|-|-||-|-|-||-|-|-||" << endl;
		}
	}
	o << "#||0|1|2||3|4|5||6|7|8||" << endl;
	return o;
}

//Print method
void Sudoku::print(){

	cout << *this << endl;
}

//Done method checks all rows, columns, and boxes for any doubles
const bool Sudoku::done(){
	return (checkHorz() && checkVert() && checkBox());
}

//Method that checks every row to make sure no doubles exist
bool Sudoku::checkHorz(){
	set<string> check;
	for (int j = 0; j < x; j++){
		for (int i = 0; i < x; i++){
			check.insert(v[x*j + i]);
		}
		if (check.size() != x){
			return false;
		}
		check.clear();
	}
	return true;
}

//Method that checks every column
bool Sudoku::checkVert(){
	set<string> check;
	for (int i = 0; i < x; i++){
		for (int j = 0; j < x; j++){
			check.insert(v[x*j + i]);
		}
		if (check.size() != x){
			return false;
		}
		check.clear();
	}
	return true;
}

//Method that check each box of 9 cells
bool Sudoku::checkBox(){
	set<string> check;
	for (int k = 0; k < x; k += boxes){
		for (int l = 0; l < x; l += boxes){
			for (int i = k; i < k + 3; i++){
				for (int j = 0; j < l + 3; j++){
					check.insert(v[x*j + i]);
				}
				
			}
			if (check.size() != x){
				return false;
			}
			check.clear();
		}
	}
	return true;
}

//Prompt method
const int Sudoku::prompt(unsigned int & a, unsigned int & b, unsigned int & c){
	string temp;
	//Start while loop for continued prompting until valid response.
	while (true){
		cout << "Please enter valid input in the form of 'x,y,value' or 'quit' to quit:";
		cin >> temp;
		cout << endl;

		if (temp == "quit"){
			return quit;
		}
		else if (count(temp.begin(), temp.end(), ',') != numcoms2){
			cout << "Invalid String, try again." << endl;
		}
		//check that coordinates given are acually on the game board,
		//as well as if the value is in the right range and the space
		//requested is not a permanant value.
		else {
			replace(temp.begin(), temp.end(), ',', ' ');
			istringstream iss(temp);
			if (iss >> a >> b >> c){
				if ((int)a >= 0 && (int)a < x && (int)b >= 0 && (int)b < x){
					if ((int)c >= minc && c <= maxc){
						if (v2[x*b + a] == ' '){
							return success;
						}
						else{
							cout << "The space requested cannot be changed." << endl;
						}

					}
					else{
						cout << "Value input is not between 1-9" << endl;
					}
				}
				else{
					cout << "Space requested is not on the board, try again." << endl;
				}
			}
			else{
				cout << "Invalid String, try again." << endl;
			}
		}
	}
}


//Draw method checks each cell for empty space
const bool Sudoku::draw(){
	for (unsigned int i = 0; i < v.size(); i++){
		if (v[i] == " "){
			return false;
		}
	}
	return true;
}

//Turn method
const int Sudoku::turn(){
	unsigned int i, j, k;
	//Start prompt method
	int valid = prompt(i, j, k);
	if (valid == quit){
		return quit;
	}
	//Set vector spot
	v[x*j + i] = k + 48;
	//Print board
	cout << *this << endl << endl;
	return 0;
}
