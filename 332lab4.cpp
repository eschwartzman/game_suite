
#include "stdafx.h"
#include "enumerations.h"
#include "game.h"

using namespace std;

//Prints out information on how to run the program if the the correct arguments were not inputed or formatted properly.
int helpful_message(char * filename){
	cout << "usage: " << endl;
	cout << "For TicTacToe: " << filename << " TicTacToe" << endl;
	cout << "For Default Gomoku: " << filename << " Gomoku" << endl;
	cout << "For Custum Gomoku: " << filename << " Gomoku" << " [Board Size] [Win Condition]" << endl << "Board Size is > or = Win Condition.  Win Condition must be > 2." << endl;
	cout << "For Sudoku: " << filename << " Sudoku" << endl;
	return badInputs;
}

//Main function that checks which game the user wants to play and if that was declared properly.
int main(int argc, char* argv[])
{

	//if an invalid number of inputs is placed for any game
	if (argc < 1 || argc >> 4){
		helpful_message(argv[filename]);
		return wrongNumInputs;
	}
	try{
	//	cout << "1" << endl;
		Game::identifier(argc, argv);
		try{
			shared_ptr<Game> g = Game::instance();
			int outcome = g->play();
			return outcome;
		}
		catch (exception *e){
			if (e->what() == "No File"){
				return nofileerror;
			}
			else if (e->what() == "Too many values"){
				return badfileerror;
			}
			else{
				cout << "Game was not able to be created" << endl;
				return badptr;
			}
			
		}
	}
	catch (bad_alloc){
		cout << "Allocation Error" << endl;
		return badAlloc;
	}
	catch (exception & ex){
		if (ex.what() == "BadInputs"){
			return helpful_message(argv[filename]);
		}
		
		if (ex.what() == "notNullSharedPtr"){
			cout << "A Game is already being played" << endl;
		}
		
	}
	catch (...){
		return helpful_message(argv[filename]);
	}


}