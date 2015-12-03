
#ifndef enumerations_H
#define enumerations_H

enum success{
	success,
	quit,
	drawgame,
	badInputs,
	wrongNumInputs,
	nofileerror,
	badfileerror
};

enum rows{
	validrows = 3,
	validstart = 1,
	totalrows = 5,
	vectorsize = 25,
	singledig = 9,
	defaultsize = 21,
	defaultwin = 5,
	defaultstrsize = 1,
};

enum names{
	filename,
	argument1,
	wantedargumentsT = 2,
	wantedargumentsG1 = 3,
	wantedargumentsG2 = 4,
	defaultcondition = 5,
	argument2 = 2,
	argument3 = 3,

};

enum cells{
	topleft = 16,
	topmiddle = 17,
	topright = 18,
	middleleft = 11,
	middle = 12,
	middleright = 13,
	bottomleft = 6,
	bottommiddle = 7,
	bottomright = 8,

};

enum coordinates{
	var1 = 0,
	comma = 1,
	var2 = 2,
	stringsize = 3,
	numcoms = 1,
	numcoms2 = 2,
	mina = 1,
	minb = 3,
	spaceswanted = 9,
	boxes = 3,
	minc = 1,
	maxc = 9


};

enum exceptions{
	badptr = 1,
	notNullPtr = 2,
	noGame = 3,
	badAlloc = 4
};
#endif
