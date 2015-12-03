
#include "stdafx.h"
#include "tictactoe.h"
#include "gomoku.h"
#include "sudoku.h"

using namespace std;

shared_ptr<Game> Game::ptr = nullptr;

Game::Game(){
	stringlength = 0;
}

//Prompts for input of piece and checks for proper format or valid move. Runs until the game is over via draw, victory, or quit.
const int Game::prompt(unsigned int & a, unsigned int & b){
	string temp;
	//Start while loop for continued prompting until valid response.
	while (true){
		cout << "Please enter valid coordinates in the form of 'x,y' or 'quit' to quit:";
		cin >> temp;
		cout << endl;

		if (temp == "quit"){
			return quit;
		}
		else if (count(temp.begin(), temp.end(), ',') != numcoms){
			cout << "Invalid String, try again." << endl;
		}
		//check that coordinates given are acually on the game board.
		else {
			replace(temp.begin(), temp.end(), ',', ' ');
			istringstream iss(temp);
			if (iss >> a >> b){
				if ((int)a > 0 && (int)a < x - 1 && (int)b>0 && (int)b < x - 1){
					if (v[x*b + a] == " "){
						return success;
					}
					else{
						cout << "This space is already filled, try again." << endl;
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

//Runs the game, checks for conditions that end the game.
const int Game::play(){
	print();
	//Start while loop for continued play until game is over.
	while (true){
		//Check for player quit
		if (turn() == quit){
			if (type != "Sudoku"){
				if (xturn){
					cout << player1 << " quit." << endl;
				}
				else{
					cout << player2 << " quit." << endl;
				}
			}
			

			string playerAns;
			while (playerAns != "y" && playerAns != "n"){
				cout << "Would you like to save this game? (y/n)" << endl;
				cin >> playerAns;
			}

			ofstream s;
			s.open(type);
			if (playerAns == "n"){
				s << "NO DATA" << endl;
				
			}
			else{
				s << type << endl;
				if (type == "Gomoku"){
					s << x << endl;
					s << win << endl;
				}
				if (type != "Sudoku"){
					s << tcount << endl;
				}
				else{
					
					for (int i = 0; i < (int)v.size(); i++){
						if (v[i] == " "){
							s << 0 << " ";
						}
						else{
							s << v[i] << " ";
						}
						if (i % x == x - 1){
							s << endl;
						}
					}

					s.close();
					s.open("sudoku0");
					for (int i = 0; i < (int)v2.size(); i++){
						if (v2[i] == ' '){
							s << 0 << " ";
						}
						else{
							s << v2[i] << " ";
						}
						if (i % x == x - 1){
							s << endl;
						}
					}
					s.close();
					return quit;
				}
				for (int i = 0; i < (int)v.size(); i++){
					s << v[i] << endl;
				}
			}
			s.close();

			return quit;
		}
		//Check for game over.
		if (done()){
			if (type != "Sudoku"){
				if (xturn){
					cout << player2 << " Wins!" << endl;
				}
				else{
					cout << player1 << " Wins!" << endl;
				}
				cout << tcount << " turns were played." << endl;
			}
			else{
				cout << "You win!" << endl;
			}
			ofstream s;
			s.open(type);
			s << "NO DATA" << endl;
			s.close();
			return success;
		}
		//Check for draw.
		if (draw()){
			if (type != "Sudoku"){
				cout << "No winning moves remain, it is a draw. " << tcount << " moves were played." << endl;
				ofstream s;
				s.open(type);
				s << "NO DATA" << endl;
				s.close();
				return drawgame;
			}
			else{
				cout << "This games is not correctly solved. Keep trying." << endl;
			}
		}
	}
}

//Checks to see which game the player wants to play.
void Game::identifier(int i, char* args[]){
	//Build a TicTacToe game
	try{
		instance();
		throw new runtime_error("notNullSharedPtr");
	}
	catch(exception *){
		if (i == wantedargumentsT && args[argument1] == string("TicTacToe")){
			ptr = make_shared<TicTacToeGame>(*(new TicTacToeGame()));
		}
		//Builds a Gomoku game under specified conditions
		else if (i == wantedargumentsG1 && args[argument1] == string("Gomoku")){ //if the user puts in 1 argument with Gomoku
			istringstream iss(args[argument2]); //checks for an input of a Board Size
			int bsize; //holds the board size
			if (iss >> bsize && bsize >= mina){
				if (bsize >= defaultcondition){
					ptr = make_shared<Gomoku>(*(new Gomoku(bsize + 2, 5)));
				}
			}
		}
		else if (i == wantedargumentsG2 && args[argument1] == string("Gomoku")){ //if the user puts in 2 argument with Gomoku
			istringstream iss(args[argument2]); //checks for an input of a Board Size
			int bsize; //holds board size
			int wcondition; //holds win condition
			if (iss >> bsize && bsize >= mina){
				istringstream iss2(args[argument3]); //Checks for an input of a win condition
				if (iss2 >> wcondition && wcondition >= minb){
					if (bsize >= wcondition){
						ptr = make_shared<Gomoku>(*(new Gomoku(bsize + 2, wcondition)));
					}
				}
			}
		}
		//Default Gomoku game if no specifed dimensions or win condtions are provided. 
		else if (i == wantedargumentsT && args[argument1] == string("Gomoku")){
				ptr = make_shared<Gomoku>(*(new Gomoku()));
		}
		else if (i == wantedargumentsT && args[argument1] == string("Sudoku")){
			try{
				ptr = make_shared<Sudoku>(*(new Sudoku()));
			}
			catch (...){

			}
		}

		 //if input was not formatted correctly, returns a nullptr indicating unable to build a board.
		if (ptr == nullptr){
			throw new runtime_error("BadInputs");
		}
		//any instance where a new Game is created, it is promptly deleted in the main function once the game is over.
	}
}

shared_ptr<Game> Game::instance(){
	if (ptr != nullptr){
		return ptr;
	}
	throw new runtime_error("nullSharedPtr");
}

