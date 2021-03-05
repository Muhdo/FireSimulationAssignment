#pragma once
#ifndef FOREST_H
#define FOREST_H

#include <iostream>
#include <vector>


#include "Cell.h"

using namespace std;

class Forest {

public:
	vector<Cell> forest = vector<Cell>();
	bool simEnded = false;
	
	vector<Cell> CreateBoundary(vector<Cell> tempForest);
	void CreateForest();
	void Print();
	void SetFire();
	void Spread();
};
#endif
