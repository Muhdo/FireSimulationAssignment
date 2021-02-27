#pragma once
#ifndef CELL_H
#define CELL_H

#include <iostream>

using namespace std;

class Position {
public:
	int x;
	int y;
	
	Position() {
		x = 0;
		y = 0;
	}
	
	Position(int x, int y);
};

class Cell {
public:
	enum Type { Empty = 0, Tree = 1, Burning = 2 };
	Type firstState;
	Type currentState;
	Position pos;
	
	Cell() {
		firstState = Tree;
		currentState = Tree;
		pos = Position();
	};
	
	Cell(int x, int y);

	void ChangeCell(Type type);
	
};

#endif

