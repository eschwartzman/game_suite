
#ifndef game_H
#define game_H

#include "enumerations.h"
#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <fstream>
#include <set>
#include <iomanip>
#include <algorithm>

using namespace std;

//Base Class
class Game{

public: //Features functions needed to be accessed in main in order to run the game.
	//public functions and friend functions
	Game();
	const int play();
	static void identifier(int i, char* args[]);
	static shared_ptr<Game> instance();
protected: //Features functions to be used by sub classes
	//game board dimensions
	int x;
	int y;
	int win;
	string player1;
	string player2;
	vector<string> v;
	int stringlength;
	int tcount;
	string type;
	bool xturn;
	string xturns;
	string oturns;
	virtual void print() = 0;
	virtual const bool done() = 0;
	virtual const bool draw() = 0;
	virtual const int turn() = 0;
	const int prompt(unsigned int & a, unsigned int & b);
	static shared_ptr<Game> ptr;
	vector<char> v2;
};
#endif