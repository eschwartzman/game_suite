
#ifndef tictactoe_H
#define tictactoe_H
#include "game.h"

//TicTacToe Game
class TicTacToeGame : public Game{
public:
	TicTacToeGame();
	virtual const bool done();
	virtual const bool draw();
	virtual const int turn();
	friend ostream & operator<< (ostream &o, const TicTacToeGame &t);
	virtual void print();
};

#endif