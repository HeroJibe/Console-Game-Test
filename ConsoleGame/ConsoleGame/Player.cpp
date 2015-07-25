#include "Player.h"

#define RED     FOREGROUND_RED
#define GREEN   FOREGROUND_GREEN
#define YELLOW  (FOREGROUND_RED | FOREGROUND_GREEN)
#define BLUE    FOREGROUND_BLUE
#define MAGENTA (FOREGROUND_RED | FOREGROUND_BLUE)
#define CYAN    (FOREGROUND_GREEN | FOREGROUND_BLUE)
#define WHITE   (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

#define INIT_X 3
#define INIT_Y 2

Player::Player()
{
	x = INIT_X;
	y = INIT_Y;
	x_old = x;
	y_old = y;
	health = 100;
}

int Player::moveY(int change)
{
	y = y + change;
	return y;
}

int Player::moveX(int change)
{
	x = x + change;
	return x;
}

void Player::draw()
{
	WriteAt("@", x, y, YELLOW, hConsole);
}

void Player::deRender(double prevX, double prevY)
{
	WriteAt(" ",prevX, prevY, 0, NULL);
}
