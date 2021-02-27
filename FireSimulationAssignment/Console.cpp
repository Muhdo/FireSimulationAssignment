#include <iostream>
#include <Windows.h>

#include "Console.h"

using namespace std;

void Console::WriteMessage(Message msg) {
	switch (msg) {
		case Start: cout << "Press ENTER to set fire to the first tree." << endl; break;
		case Next: cout << "Press ENTER to move to the next iteration." << endl; break;
		case End: cout << "Simulation ended, press ENTER to restart." << endl; break;
	}
}

void Console::ChangeCursorVisibility(bool visibility) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = visibility; //Change visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void Console::SetCursorPosition(int x, int y) {
	//Initialize objects for cursor manipulation
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	//Position cursor at start of window
	destCoord.X = x;
	destCoord.Y = y;
	SetConsoleCursorPosition(hStdout, destCoord); //Move cursor to the location
}

void Console::EndSimulation(int y) {
	SetCursorPosition(0, y);
	WriteMessage(End);
}