#pragma once
#ifndef FOREST_H
#define FOREST_H

#include <vector>
#include "Cell.h"

class Forest {

	bool simEnded = false;
public:
	vector<Cell> forest = vector<Cell>();
	
	bool SimEnded();
	void CreateBoundary();
	void CreateForest();
	void Print();
	void SetFire();
	void Spread();
	void SpawnNewTrees();
};
#endif
