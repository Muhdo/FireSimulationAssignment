#pragma once
#ifndef FOREST_H
#define FOREST_H

#include <iostream>
#include <vector>


#include "Cell.h"

using namespace std;

class Forest {
	//2D array with pointers
	// Cell forest[21][21];
	
	// Cell(*forestP)[21][21] = &forest;
	// (*aptr)[i][j] read 2D array in pointer

public:
	vector<Cell> forest = vector<Cell>();
	
	vector<Cell> CreateBoundary(vector<Cell> tempForest);
	void CreateForest();
	void Print();
};


class Grid {
	
	void Spread();
};
#endif
