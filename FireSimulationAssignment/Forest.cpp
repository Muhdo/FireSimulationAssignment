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
	/*
	 * This generator generates floating values from 0.(0) to 1.(9)
	 *            Empty | Tree
	 * 0,   2   = 50%     50%
	 * 0.5, 2   = 25%     75%
	 * 0,   1.5 = 75%     25%
	 * 0.5, 1.5 = 50%     50%
	 *
	 * When casting to integer only the left side is passed.
	 * 
	 * Less probability of Empty:
	 * Change Lower value between 0.0 - 0.(9)
	 * 
	 * Less probability of Tree:
	 * Change Upper value between 1.(1) - 2.0
	 */
	
	//Random generator stuff
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> forestRandom(0.5, 2); //Random between 0 and 1 (0=Empty; 1=Tree)

	vector<Cell> tempForest = vector<Cell>(); //Creates temporary forest
	
	for (int i = 0; i < 21; ++i) //Y axis
		for (int j = 0; j < 21; ++j) //X axis
			if ((int)forestRandom(gen) == 1) //Generates number and if is a tree it will add
				tempForest.push_back(Cell(i, j)); //Add tree to array
					
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


//Search in vector and return index
template <typename T, typename T2>
pair<bool, int> findInVector(const std::vector<T>  & vec, const T2  & pos) {
    pair<bool, int > result; //First: Was Found | Second: Index

	//Finds the position in the vector
    auto it = find(vec.begin(), vec.end(), pos);

	//If it was found
	if (it != vec.end()) {
        result.second = distance(vec.begin(), it); //Give index in vector
        result.first = true; //Sets as found
    } else {
        result.second = -1; //Give index of -1
        result.first = false; //Sets as not found
    }

	return result;
}

void Forest::SetFire() {
	pair<bool, int> arrayPos = findInVector(forest, Position(10, 10)); //Searches the vector for the middle position of the forest

	/*
	 * Moving one iteration forward makes sense even if its to the same type
	 *
	 * CurrentState = Tree | PreviousState = Empty
	 * It's right after the cell is created
	 *
	 * CurrentState = Tree | PreviousState = Tree
	 * Tells that isn't the first iteration of the tree
	 */
	
	//For each cell in the forest
	for (Cell cell : forest)
		if (cell.currentState == Cell::Tree) //Checks if its a tree
			cell.ChangeCell(Cell::Tree); //Moves one Iteration forward

	if (arrayPos.first == true) //If was found
		forest[arrayPos.second].ChangeCell(Cell::Burning); //Makes the tree burn
	else //If wasn't found
		forest.push_back(Cell(10, 10, Cell::Burning)); //Creates a cell in the middle
}

void Forest::Spread() {
	/*
	 * This generator generates floating values from 0.(0) to 1.(9)
	 *            Don't Burn | Burn
	 * 0,   2   =    50%       50%
	 * 0.5, 2   =    25%       75%
	 * 0,   1.5 =    75%       25%
	 * 0.5, 1.5 =    50%       50%
	 *
	 * When casting to integer only the left side is passed.
	 * 
	 * Less probability of not burning:
	 * Change Lower value between 0.0 - 0.(9)
	 * 
	 * Less probability of burning:
	 * Change Upper value between 1.(1) - 2.0
	 */
	
	//Random generator stuff
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> burnRandom(0, 2); //Random between 0 and 1 (0=Don't Burn; 1=Burn)
	
	vector<Cell> tempForest = forest; //Gets a copy of the current forest

	simEnded = true;
	
	//For each cell in the forest
	for (int i = 0; i < forest.size(); ++i) {
		if (forest[i].currentState == Cell::Burning) { //Checks if the current cell is burning
			bool changeIteration = true; //To know if the current cell should move to the next iteration

			Cell current = forest[i]; //Data about the current cell

			/*	Horizontal: X | Vertical: Y
			 *	
			 *	-1, -1 |  0, -1 | +1, -1
			 *	------------------------
			 *	-1,  0 |  0,  0 | +1,  0
			 *	------------------------
			 *	-1, +1 |  0, +1 | +1, +1
			 *
			 *	Current: X,   Y
			 *	-----------------
			 *	  North: X,   Y-1
			 *	  South: X,   Y+1
			 *	   West: X-1, Y
			 *	   East: X+1, Y
			 */

			//Get North Cell from Current
			current.pos.y--;			
			pair<bool, int> north = findInVector(forest, current.pos);

			//Get South Cell from Current
			current.pos.y += 2;			
			pair<bool, int> south = findInVector(forest, current.pos);

			//Get West Cell from Current
			current.pos.y--;
			current.pos.x--;
			pair<bool, int> west = findInVector(forest, current.pos);

			//Get East Cell from Current
			current.pos.x += 2;
			pair<bool, int> east = findInVector(forest, current.pos);

			if (north.first || south.first || west.first || east.first) 
				simEnded = false;
			
			//Checks if any of those cells are trees and make it burn with 50% chance
			if (north.first == true && tempForest[north.second].currentState == Cell::Tree)
				if ((int)burnRandom(gen) == 1) //Burn
					tempForest[north.second].ChangeCell(Cell::Burning);	
				else changeIteration = false; //Don't Burn and don't change iteration
				
			if (south.first == true && tempForest[south.second].currentState == Cell::Tree)
				if ((int)burnRandom(gen) == 1) //Burn
					tempForest[south.second].ChangeCell(Cell::Burning);
				else changeIteration = false; //Don't Burn and don't change iteration
			
			if (west.first == true && tempForest[west.second].currentState == Cell::Tree)
				if ((int)burnRandom(gen) == 1) //Burn
					tempForest[west.second].ChangeCell(Cell::Burning);
				else changeIteration = false; //Don't Burn and don't change iteration
			
			if (east.first == true && tempForest[east.second].currentState == Cell::Tree)
				if ((int)burnRandom(gen) == 1) //Burn
					tempForest[east.second].ChangeCell(Cell::Burning);
				else changeIteration = false; //Don't Burn and don't change iteration	


			if (changeIteration) tempForest[i].ChangeCell(Cell::Burning); //Move to the next iteration
		}
	}
	
	forest = tempForest; //Copies temporary forest to main forest

	vector<Cell>::iterator it = forest.begin(); //Forest iterator

	//Goes through every cell in the forest
	while (it != forest.end())
		if (it->previousState == Cell::Burning && it->currentState == Cell::Burning) //Checks if is burning at 2 iterations
			it = forest.erase(it); //Deletes cell
		else ++it; //Moves to next cell
		
}

