#include "Console.h"

#include <iostream>

#include "Forest.h"

using namespace std;

int main() {
	Console cns;

	cns.ChangeCursorVisibility(false);
	while (true) {
		Forest map = Forest();

		map.CreateBoundary();
		
		map.CreateForest();
		map.Print();

		cns.ChangeCursorColor(15);
		cns.SetCursorPosition(0, 23);
		cns.WriteMessage(Console::Start);
		
		getchar();
		map.SetFire();
		map.Print();

		cns.ChangeCursorColor(15);
		cns.SetCursorPosition(0, 23);
		cns.WriteMessage(Console::Next);

		while (!map.SimEnded()) {	
			getchar();
			
			map.Spread();
			map.Print();
		}

		cns.ChangeCursorColor(15);
		cns.EndSimulation(23);
		getchar();
		system("cls");
	}
}
