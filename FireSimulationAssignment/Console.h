#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>

using namespace std;

class Console {
public:

	enum Message {Start, Next, End};

	static void WriteMessage(Message msg);
	static void ChangeCursorVisibility(bool visibility);
	static void SetCursorPosition(int x, int y);
	static void EndSimulation(int y);
};

#endif