#include "Cell.h"

Position::Position(int _x, int _y) {
	x = _x;
	y = _y;
}

Cell::Cell(int _x, int _y) {
	previousState = Empty;
	currentState = Tree;
	pos = Position(_x, _y);
}

Cell::Cell(int _x, int _y, Type type) {
	previousState = Empty;
	currentState = type;
	pos = Position(_x, _y);
}

void Cell::ChangeCell(Type type) {
	previousState = currentState;
	currentState = type;
}
