
#ifndef gomoku_H
#define gomoku_H
#include "game.h"

//Gomoku Game
class Gomoku : public Game{
private:
	int lastpiece;

public:
	Gomoku(int size, int win);
	Gomoku();
	friend ostream & operator<< (ostream &o, const Gomoku &t);
	virtual void print();
	virtual const bool done();
	virtual const bool draw();
	virtual const int turn();
	int checkvert(int i, string letter);
	int checkhor(int i, string letter);
	int checkdiag1(int i, string letter);
	int checkdiag2(int i, string letter);
	int dcheckvert(int i, string letter);
	int dcheckhor(int i, string letter);
	int dcheckdiag1(int i, string letter);
	int dcheckdiag2(int i, string letter);
};

#endif