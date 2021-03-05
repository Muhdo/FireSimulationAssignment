#include "Console.h"

#include <iostream>

#include "Forest.h"

using namespace std;

int main() {
	while (true) {
		Forest map = Forest();
		
		map.CreateForest();
		map.Print();
		
		Console::SetCursorPosition(0, 22);
		Console::WriteMessage(Console::Start);
		
		getchar();
		map.SetFire();
		map.Print();

		while (!map.simEnded) {	
			Console::SetCursorPosition(0, 22);
			Console::WriteMessage(Console::Next);
			getchar();
			
			map.Spread();
			map.Print();
		}
		
		Console::EndSimulation(22);
		getchar();
		system("cls");
	}
}
