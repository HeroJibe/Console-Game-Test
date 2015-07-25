#pragma once
#include <windows.h>

using namespace System;

void WriteAt(String^ s, double x, double y, WORD, HANDLE);

#define INIT_X 3
#define INIT_Y 2

class Player
{
public:

	double x;
	double y;
	double x_old;
	double y_old;
	int health;
	HANDLE hConsole;

	Player();
	int moveY(int);
	int moveX(int);
	void draw();
	void deRender(double, double);
};

