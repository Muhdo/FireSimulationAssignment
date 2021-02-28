#include "Cell.h"
#include "Forest.h"

#include <random>

#include "Console.h"


vector<Cell> Forest::CreateBoundary(vector<Cell> tempForest) {
	//Random generator stuff
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> positionRandom(1, 21); //Random between 1 and 20 (Generates a number between the second and last but one cell of the forest)
	uniform_real_distribution<> orientationRandom(0, 2); //Random between 0 and 1 (0 = Horizontal, 1 = Vertical)

	int boundary = positionRandom(gen); //Position of boundary
	int orientation = orientationRandom(gen); //Orientation of boundary

	//Selects the orientation
	if (orientation == 0) { //Horizontal boundary
		for (int i = 0; i < tempForest.size(); ++i) { //Goes through every item in the vector
			if (tempForest[i].pos.y == boundary) { //Checks the y position of the item
				tempForest.erase(tempForest.begin() + i); //Deletes the item if is in the Y position of boundary
			}
		}
	} else if (orientation == 1) { //Vertical boundary
		for (int i = 0; i < tempForest.size(); ++i) { //Goes through every item in the vector
			if (tempForest[i].pos.x == boundary) { //Checks the y position of the item
				tempForest.erase(tempForest.begin() + i--); //Deletes the item if is in the Y position of boundary
			}
		}
	}

	return tempForest;
}

void Forest::CreateForest() {
	//Random generator stuff
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> forestRandom(0, 2); //Random between 0 and 1 (0=Empty; 1=Tree)

	vector<Cell> tempForest = vector<Cell>(); //Creates temporary forest
	
	for (int i = 0; i < 21; ++i) //Y axis
		for (int j = 0; j < 21; ++j) //X axis
			//if ((int)forestRandom(gen) == 1) //generates number and if is a tree it will add
				tempForest.push_back(Cell(i, j)); //add tree to array
					
	forest = CreateBoundary(tempForest); //Creates boundary and saves forest
}

void Forest::Print() {
	//For each item in the array
	for (int i = 0; i < forest.size(); ++i) {
		Cell crtCell = forest[i]; //gets the current item
		if (crtCell.previousState == Cell::Empty && crtCell.currentState == Cell::Tree) {
			Console::SetCursorPosition(crtCell.pos.x * 2, crtCell.pos.y); //Move to position of cell (X * 2 so the map looks like a square in the map)
			cout << (char)6; //Prints ASCII character number 6 which is a spade
		} else if (crtCell.previousState == Cell::Empty && crtCell.currentState == Cell::Burning) {
			Console::SetCursorPosition(crtCell.pos.x * 2, crtCell.pos.y); //Move to position of cell (X * 2 so the map looks like a square in the map)
			cout << (char)15; //Prints ASCII character number 15 which looks like flame
		} else if (crtCell.previousState == Cell::Tree && crtCell.currentState == Cell::Burning) {
			Console::SetCursorPosition(crtCell.pos.x * 2, crtCell.pos.y); //Move to position of cell (X * 2 so the map looks like a square in the map)
			cout << (char)15; //Prints ASCII character number 15 which looks like flame
		}
	}
}

void Forest::SetFire() {
	int arrayPos = -1;
	
	for (int i = 0; i < forest.size(); ++i) 
		if (forest[i].pos.x == 10 && forest[i].pos.y == 10) {
			arrayPos = i;
			break;
		}

	if (arrayPos != -1) {
		forest[arrayPos].ChangeCell(Cell::Burning);
	} else {
		forest.push_back(Cell(10, 10, Cell::Burning));
	}
}

template <typename T, typename T2>
pair<bool, int> findInVector(const std::vector<T>  & vecOfElements, const T2  & element)
{
    pair<bool, int > result;
    // Find given element in vector
    auto it = find(vecOfElements.begin(), vecOfElements.end(), element);
    if (it != vecOfElements.end())
    {
        result.second = distance(vecOfElements.begin(), it);
        result.first = true;
    }
    else
    {
        result.first = false;
        result.second = -1;
    }
    return result;
}


void Forest::Spread() {
	vector<Cell> tempForest = forest;
	
	for (int i = 0; i < forest.size(); ++i) {
		if (forest[i].currentState == Cell::Burning && forest[i].previousState != Cell::Burning) {
			Cell current = forest[i]; 

			current.pos.y--;			
			pair<bool, int> north = findInVector(forest, current.pos);

			current.pos.y = current.pos.y + 2;			
			pair<bool, int> south = findInVector(forest, current.pos);

			current.pos.y--;
			current.pos.x--;
			pair<bool, int> west = findInVector(forest, current.pos);

			current.pos.x = current.pos.x + 2;
			pair<bool, int> east = findInVector(forest, current.pos);

			if (north.first == true) {
				tempForest[north.second].ChangeCell(Cell::Burning);
			}
			if (south.first == true) {
				tempForest[south.second].ChangeCell(Cell::Burning);
			}
			if (west.first == true) {
				tempForest[west.second].ChangeCell(Cell::Burning);
			}
			if (east.first == true) {
				tempForest[east.second].ChangeCell(Cell::Burning);
			}
		}
	}

	forest = tempForest;
}

