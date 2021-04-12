#pragma once
#ifndef FOREST_H
#define FOREST_H

#include <vector>
#include "Cell.h"

class Forest {

	double windDirection[2] = { 0, 0 };
	bool simEnded = false;
public:
	vector<Cell> forest = vector<Cell>();
	
	bool SimEnded();
	void CreateBoundary();
	void CreateForest();
	void Print();
	void SetFire();
	bool BurnCalculation(char dir);
	void Spread();
	void SpawnNewTrees();
	void WindSimulation();
};
#endif
