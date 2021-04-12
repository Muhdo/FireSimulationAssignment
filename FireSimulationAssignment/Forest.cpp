#include "Cell.h"
#include "Forest.h"

#include <random>
#include <Windows.h>

#include "Console.h"

Console* cns;

bool Forest::SimEnded() {
	return simEnded;
}

void Forest::CreateBoundary() {
	cns->ChangeCursorColor(15);
	
	cout << (char)201;
	for(int i = 0; i < 41; ++i) //21 * 2 - 1 --- The 21 cells, the space between each cell and one less in the end
		cout << (char)205;
	cout << (char)187;

	for (int i = 0; i < 21; ++i) {
		cns->SetCursorPosition(0, i + 1);
		cout << (char)186;
		cns->SetCursorPosition(42, i + 1);
		cout << (char)186;
	}

	cns->SetCursorPosition(0, 22);
	cout << (char)200;
	for(int i = 0; i < 41; ++i) //21 * 2 - 1 --- The 21 cells, the space between each cell and one less in the end
		cout << (char)205;
	cout << (char)188;
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
	
	for (int y = 0; y < 21; ++y) //Y axis
		for (int x = 0; x < 21; ++x) //X axis
			if ((int)forestRandom(gen) == 1) //Generates number and if is a tree it will add
				tempForest.push_back(Cell(x, y)); //Add tree to array
					
	forest = tempForest; //Saves forest
}

void Forest::Print() {
	//Clears the screen so old fires don't show
	for (int y = 1; y < 22; y++) {
		cns->SetCursorPosition(1, y);
		cout << "                                         ";
	}

	//For each item in the array
	for (int i = 0; i < forest.size(); ++i) {
		Cell crtCell = forest[i]; //Gets the current item
		
		//(X * 2 so the map looks like a square in the map)
		if (crtCell.GetCurrentState() == Cell::Tree) {
			cns->SetCursorPosition(crtCell.GetPosition().x * 2 + 1, crtCell.GetPosition().y + 1); //Move to position of cell
			if (!simEnded)
				cns->ChangeCursorColor(10);
			else
				cns->ChangeCursorColor(15);
			cout << (char)6; //Prints ASCII character number 6 which is a spade
		} else if (crtCell.GetCurrentState() == Cell::Burning) {
			cns->SetCursorPosition(crtCell.GetPosition().x * 2 + 1, crtCell.GetPosition().y + 1); //Move to position of cell
			if (!simEnded)
				cns->ChangeCursorColor(12);
			else
				cns->ChangeCursorColor(15);
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
		if (cell.GetCurrentState() == Cell::Tree) //Checks if its a tree
			cell.ChangeCell(Cell::Tree); //Moves one Iteration forward

	if (arrayPos.first == true) //If was found
		forest[arrayPos.second].ChangeCell(Cell::Burning); //Makes the tree burn
	else //If wasn't found
		forest.push_back(Cell(10, 10, Cell::Burning)); //Creates a cell in the middle

	WindSimulation();
}

bool Forest::BurnCalculation(char dir) {
	//Random generator stuff
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> burnVRandom(0, fabs(windDirection[1] + 1)); //Does the tree burn? for vertical axis
	uniform_real_distribution<> burnHRandom(0, fabs(windDirection[0] + 1)); //Does the tree burn? for horizontal axis
	uniform_real_distribution<> burnRandom(0, 1); //Does the tree burn? no axis

	//Checks the direction its trying to burn and if the wind is blowing in the same direction
	if (dir == 'N' && windDirection[1] > 0)
		//Random for the tree to burn or not
		if (burnVRandom(gen) > 0.5)
			return true;
		else
			return false;
	else if (dir == 'S' && windDirection[1] < 0)
		//Random for the tree to burn or not
		if (burnVRandom(gen) > 0.5)
			return true;
		else
			return false;
	else if (dir == 'W' && windDirection[0] < 0)
		//Random for the tree to burn or not
		if (burnHRandom(gen) > 0.5)
			return true;
		else
			return false;
	else if (dir == 'E' && windDirection[0] > 0)
		//Random for the tree to burn or not
		if (burnHRandom(gen) > 0.5)
			return true;
		else
			return false;

	//Random for the tree to burn or not
	if (burnRandom(gen) > 0.5)
		return true;
	else
		return false;
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
		if (forest[i].GetCurrentState() == Cell::Burning) { //Checks if the current cell is burning
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


			Position pos = current.GetPosition();
			//Get North Cell from Current
			pos.y--;
			pair<bool, int> north = findInVector(forest, pos);

			//Get South Cell from Current
			pos.y += 2;			
			pair<bool, int> south = findInVector(forest, pos);

			//Get West Cell from Current
			pos.y--;
			pos.x--;
			pair<bool, int> west = findInVector(forest, pos);

			//Get East Cell from Current
			pos.x += 2;
			pair<bool, int> east = findInVector(forest, pos);

			if (north.first || south.first || west.first || east.first) 
				simEnded = false;
			
			//Checks if any of those cells are trees and make it burn with 50% chance
			if (north.first == true && tempForest[north.second].GetCurrentState() == Cell::Tree)
				if (BurnCalculation('N')) //Burn
					tempForest[north.second].ChangeCell(Cell::Burning);	
				else changeIteration = false; //Don't Burn and don't change iteration
				
			if (south.first == true && tempForest[south.second].GetCurrentState() == Cell::Tree)
				if (BurnCalculation('S')) //Burn
					tempForest[south.second].ChangeCell(Cell::Burning);
				else changeIteration = false; //Don't Burn and don't change iteration
			
			if (west.first == true && tempForest[west.second].GetCurrentState() == Cell::Tree)
				if (BurnCalculation('W')) //Burn
					tempForest[west.second].ChangeCell(Cell::Burning);
				else changeIteration = false; //Don't Burn and don't change iteration
			
			if (east.first == true && tempForest[east.second].GetCurrentState() == Cell::Tree)
				if (BurnCalculation('E')) //Burn
					tempForest[east.second].ChangeCell(Cell::Burning);
				else changeIteration = false; //Don't Burn and don't change iteration	


			if (changeIteration) tempForest[i].ChangeCell(Cell::Burning); //Move to the next iteration
		}
	}
	
	forest = tempForest; //Copies temporary forest to main forest

	WindSimulation();
	SpawnNewTrees();

	vector<Cell>::iterator it = forest.begin(); //Forest iterator

	//Goes through every cell in the forest
	while (it != forest.end())
		if (it->GetPreviousState() == Cell::Burning && it->GetCurrentState() == Cell::Burning) //Checks if is burning at 2 iterations
			it = forest.erase(it); //Deletes cell
		else ++it; //Moves to next cell
		
}

void Forest::SpawnNewTrees() {
	//Random generator stuff
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> probabilityRandom(0, 1.1); //Probability of current cell to spawn a tree (values goes between (double)0.0 and (double)1.0(9))
	uniform_real_distribution<> amountRandom(0, 21 * 21 - forest.size()); //Random amount between the available spaces
	uniform_real_distribution<> posRandom(0, 21); //Random position in the forest

	//For the amount of tries available to spawn a tree
	for (int i = 0; i < (int)amountRandom(gen); i++) {
		//Generates a random position (available or not)
		int x = posRandom(gen);
		int y = posRandom(gen);

		//Checks if its available
		pair<bool, int> place = findInVector(forest, Position(x, y));

		//If it's available and the probability to spawn a tree is set to 1
		if (!place.first && (int)probabilityRandom(gen) == 1)
			forest.push_back(Cell(x, y)); //Spawns a tree
	}
}

void Forest::WindSimulation() {
	//Random generator stuff
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dirRandom(-1, 1); //amount to change the wind
	
	windDirection[0] = dirRandom(gen);
	windDirection[1] = dirRandom(gen);

	cns->SetCursorPosition(0, 29);
	cns->ChangeCursorColor(15);
	cout << "                                 ";
	cns->SetCursorPosition(0, 27);
	cout << "Next Iteration" << endl << "--------------" << endl;
	
	if (windDirection[1] > 0)
		cout << "North " << floor((windDirection[1] * 10) / 0.01) * 0.01 << "Km/h  ";
	else if (windDirection[1] < 0)
		cout << "South " << floor((windDirection[1] * -10) / 0.01) * 0.01 << "Km/h  ";
	
	if (windDirection[0] > 0)
		cout << "East " << floor((windDirection[0] * 10) / 0.01) * 0.01 << "Km/h";
	else if (windDirection[0] < 0)
		cout << "West " << floor((windDirection[0] * -10) / 0.01) * 0.01 << "Km/h";
}