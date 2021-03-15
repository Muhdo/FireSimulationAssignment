#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

class Console {
public:
	enum Message {Start, Next, End};

	void WriteMessage(Message msg);
	void ChangeCursorColor(int color);
	void ChangeCursorVisibility(bool visibility);
	void SetCursorPosition(int x, int y);
	void EndSimulation(int y);
};

#endif