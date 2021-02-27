#include "Cell.h"

Position::Position(int _x, int _y) {
	x = _x;
	y = _y;
}

Cell::Cell(int _x, int _y) {
	firstState = Tree;
	currentState = Tree;
	pos = Position(_x, _y);
}


void Cell::ChangeCell(Type type) {
	currentState = type;
}
