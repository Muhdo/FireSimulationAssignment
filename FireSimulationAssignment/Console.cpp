#include <iostream>
#include <Windows.h>
#include <vector>

#include "Console.h"
#include "Cell.h"

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Console::WriteMessage(Message msg) {
	cout << "-------------------------------------------" << endl;
	
	switch (msg) {
		case Start: cout << " Press ENTER to set fire to the first tree." << endl; break;
		case Next: cout <<  " Press ENTER to move to the next iteration." << endl; break;
		case End: cout <<   " Simulation ended, press ENTER to restart. " << endl; break;
	}

	cout << "-------------------------------------------" << endl;
}

void Console::ChangeCursorVisibility(bool visibility) {
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = visibility; //Change visibility
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Console::ChangeCursorColor(int color) {
	//10 = Green
	//14 = Yellow
	//15 = White
	
	SetConsoleTextAttribute(hConsole, color);
}


void Console::SetCursorPosition(int x, int y) {
	COORD destCoord;

	//Position cursor at start of window
	destCoord.X = x;
	destCoord.Y = y;
	SetConsoleCursorPosition(hConsole, destCoord); //Move cursor to the location
}

void Console::EndSimulation(int y) {
	SetCursorPosition(0, y);
	WriteMessage(End);
}