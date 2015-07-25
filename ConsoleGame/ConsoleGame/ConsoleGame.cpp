#include <windows.h>
#include "stdafx.h"
#include <stdio.h>
#include "Player.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Entity.h"

using namespace System;

#define RED     FOREGROUND_RED
#define GREEN   FOREGROUND_GREEN
#define DARK_GREEN   (FOREGROUND_GREEN | FOREGROUND_INTENSITY)

#define YELLOW  (FOREGROUND_RED | FOREGROUND_GREEN)
#define BLUE    FOREGROUND_BLUE
#define MAGENTA (FOREGROUND_RED | FOREGROUND_BLUE)
#define CYAN    (FOREGROUND_GREEN | FOREGROUND_BLUE)
#define WHITE   (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

#define MAP_WIDTH 30
#define MAP_HEIGHT 20
#define COVERAGE 0.25f

#define MOVE_SPEED_Y 0.00001
#define MOVE_SPEED_X 0.00003


int origRow;
int origCol;

struct MAP {
	unsigned char type;
};

void WriteAt(String^ s, double x, double y, WORD color, HANDLE hConsole)
{
	try
	{
		if (hConsole != NULL)
			SetConsoleTextAttribute(hConsole, color);
		Console::SetCursorPosition((int) (origCol + x), (int) (origRow + y));
		Console::Write(s);
		SetConsoleTextAttribute(hConsole, WHITE);

	}
	catch (ArgumentOutOfRangeException^ e)
	{
		Console::Clear();
		Console::WriteLine(e->Message);
	}
}

bool Collision(Player *PLAYER, Entity *Entities);
void drawMap();
void generateMap(MAP *Map_ptr, Entity *Entities);
void drawFeatures(MAP *Map_ptr, Entity *Entities, HANDLE hconsole);

int main()
{
	int temp;
	int i;
	bool key_press = false;
	MAP *MAP_ptr;
	Entity Entities;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	MAP_ptr = (MAP*)malloc(MAP_HEIGHT * MAP_WIDTH * sizeof(MAP));

	Player PLAYER;
	PLAYER.hConsole = hConsole;

	// Clear the screen, then save the top and left coordinates.
	Console::Clear();
	origRow = Console::CursorTop;
	origCol = Console::CursorLeft;

	temp = MAP_HEIGHT + 2;
	i = 0;

	PLAYER.draw();
	drawMap();
	generateMap(MAP_ptr, &Entities);
	drawFeatures(MAP_ptr, &Entities, hConsole);

	while (1)
	{
		if (GetAsyncKeyState(0x57)) /*W*/
		{
			PLAYER.y -= MOVE_SPEED_Y;
			if (Collision(&PLAYER, &Entities))
				PLAYER.y += MOVE_SPEED_Y;
			else
				if ((int)(PLAYER.y) != (int)(PLAYER.y_old))
				{
					PLAYER.draw();
					PLAYER.deRender(PLAYER.x, PLAYER.y_old);
					PLAYER.y_old = PLAYER.y;
				}
		}
		else if (GetAsyncKeyState(0x53)) /*S*/
		{
			PLAYER.y += MOVE_SPEED_Y;
			if (Collision(&PLAYER, &Entities))
				PLAYER.y -= MOVE_SPEED_Y;
			else
				if ((int)(PLAYER.y) != (int)(PLAYER.y_old))
				{
					PLAYER.draw();
					PLAYER.deRender(PLAYER.x, PLAYER.y_old);
					PLAYER.y_old = PLAYER.y;
				}
		}
		else if (GetAsyncKeyState(0x41)) /*A*/
		{
			PLAYER.x -= MOVE_SPEED_X;
			if (Collision(&PLAYER, &Entities))
				PLAYER.x += MOVE_SPEED_X;
			else
				if ((int)(PLAYER.x) != (int)(PLAYER.x_old))
				{
					PLAYER.draw();
					PLAYER.deRender(PLAYER.x_old, PLAYER.y);
					PLAYER.x_old = PLAYER.x;
				}
		}
		else if (GetAsyncKeyState(0x44)) /*D*/
		{
			PLAYER.x += MOVE_SPEED_X;
			if (Collision(&PLAYER, &Entities))
				PLAYER.x -= MOVE_SPEED_X;
			else
			if ((int)(PLAYER.x) != (int)(PLAYER.x_old))
			{
				PLAYER.draw();
				PLAYER.deRender(PLAYER.x_old, PLAYER.y);
				PLAYER.x_old = PLAYER.x;
			}
		}
		else if (GetAsyncKeyState(VK_END)) /**/
			return 1;

		/*Border Collisions*/
		if (PLAYER.y >= MAP_HEIGHT - 1)
		{
			PLAYER.y -= 1;
			drawMap();
		}
		else if (PLAYER.y <= 2)
		{
			PLAYER.y = 3;
			drawMap();
		}
		else if (PLAYER.x >= MAP_WIDTH - 1)
		{
			PLAYER.x -= 1;
			drawMap();
		}
		else if (PLAYER.x <= 2)
		{
			PLAYER.x = 3;
			drawMap();
		}
	}
}

bool Collision(Player *PLAYER, Entity *Entities)
{
	int counter;

	/*Entity Collisions*/
	for (counter = 0; counter <= Entities->count; counter++)
	{
		if ((int)PLAYER->y == Entities->ypos[counter] && (int)PLAYER->x == Entities->xpos[counter])
			return true;
	}
	return false;
}

void drawMap()
{
	int i;

	for (i = 0; i <= MAP_WIDTH; i++)
		WriteAt("#", i, 0, 0, NULL);

	for (i = 0; i <= MAP_WIDTH; i++)
		WriteAt("#", i, MAP_HEIGHT, 0, NULL);

	for (i = 0; i <= MAP_HEIGHT; i++)
		WriteAt("#", 0, i, 0, NULL);

	for (i = 0; i <= MAP_HEIGHT; i++)
		WriteAt("#", MAP_WIDTH, i, 0, NULL);
}

void generateMap(MAP *Map_ptr, Entity *Entities)
{
	int count = (int) ((double)(MAP_WIDTH * MAP_HEIGHT) * COVERAGE);
	int i;
	int j;
	int xpos, ypos, type;

	Entities->Create(count);

	for (j = 0; j < MAP_HEIGHT; j++)
	{
		for (i = 0; i < MAP_WIDTH; i++)
		{
			if (j == 0 || j == (MAP_HEIGHT - 1) || i == 0 || i == (MAP_WIDTH - 1))
				Map_ptr[i + MAP_WIDTH * j].type = 0;
			else
				Map_ptr[i + MAP_WIDTH * j].type = 1;
		}
	}

	for (i = 0; i < count; i++)
	{
		xpos = (rand() % (MAP_WIDTH - 2) + 1);
		ypos = (rand() % (MAP_HEIGHT - 2) + 1);
		type = rand() % 1 + 2;
		Map_ptr[xpos + MAP_WIDTH * ypos].type = type;
		Entities->Init(i, xpos, ypos, type);
	}
}

void drawFeatures(MAP *Map_ptr, Entity *Entities, HANDLE hConsole)
{
	int count = Entities->count;
	int i;

	for (i = 0; i < count; i++)
	{
		if (Entities->type[i] == 2)
		{
			WriteAt("T", Entities->xpos[i], Entities->ypos[i], GREEN, hConsole);
		}
		else if (Entities->type[i] == 3)
		{
			WriteAt("B", Entities->xpos[i], Entities->ypos[i], DARK_GREEN, hConsole);
		}

	}
}

/*▲ ☁*/