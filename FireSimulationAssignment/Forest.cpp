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
			if ((int)forestRandom(gen) == 1) //generates number and if is a tree it will add
				tempForest.push_back(Cell(i, j)); //add tree to array
					
	forest = CreateBoundary(tempForest); //Creates boundary and saves forest
}

void Forest::Print() {
	Console csl = Console(); //Gets Console class

	//For each item in the array
	for (int i = 0; i < forest.size(); ++i) {
		Cell crtCell = forest[i]; //gets the current item
		if (crtCell.currentState == Cell::Tree) { //Checks if it's a tree
			csl.SetCursorPosition(crtCell.pos.x * 2, crtCell.pos.y); //Move to position of cell (X * 2 so the map looks like a square in the map)
			cout << (char)6; //Prints ASCII character number 6 which is a spade
		} else if (crtCell.currentState == Cell::Burning) {
			csl.SetCursorPosition(crtCell.pos.x * 2, crtCell.pos.y); //Move to position of cell (X * 2 so the map looks like a square in the map)
			cout << (char)15; //Prints ASCII character number 6 which is a spade
		}
	}
}

void Grid::Spread() {  }

