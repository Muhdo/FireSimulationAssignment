#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>

using namespace std;

class Console {
public:
	enum Message {Start, Next, End};

	void WriteMessage(Message msg);
	void ChangeCursorVisibility(bool visibility);
	void SetCursorPosition(int x, int y);
	void EndSimulation(int y);
};

#endif