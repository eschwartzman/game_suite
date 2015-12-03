
#ifndef sudoku_H
#define sudoku_H
#include "game.h"

class Sudoku : public Game{
public:
	Sudoku();
	friend ostream & operator<< (ostream &o, const Sudoku &t);
	virtual void print();
	virtual const bool done();
	virtual const bool draw();
	virtual const int turn();
	const int prompt(unsigned int & a, unsigned int & b, unsigned int & c);
	bool checkHorz();
	bool checkVert();
	bool checkBox();

};

#endif