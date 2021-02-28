#pragma once
#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <string>

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
	bool operator==(Position rhs) const {
		string thisPos = to_string(this->pos.x) + ":" + to_string(this->pos.y);
		string rhsPos = to_string(rhs.x) + ":" + to_string(rhs.y);
	
		return thisPos == rhsPos;
	}

	enum Type { Empty = 0, Tree = 1, Burning = 2 };
	Type previousState;
	Type currentState;
	Position pos;
	
	Cell() {
		previousState = Empty;
		currentState = Tree;
		pos = Position();
	};
	
	Cell(int x, int y);
	Cell(int x, int y, Type type);

	void ChangeCell(Type type);
	
};

#endif

