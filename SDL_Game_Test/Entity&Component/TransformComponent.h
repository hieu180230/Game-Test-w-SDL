#pragma once
#include "Components.h"

class TransformComponent : public Component
{
private:
	int x, y;
public:

	TransformComponent()
	{
		x = 0;
		y = 0;
	}

	void init() override
	{
		x = 0;
		y = 0;
	}

	TransformComponent(int xpos, int ypos)
	{
		x = xpos;
		y = ypos;
	}

	void update() override
	{
		x++;
		y++;
	}

	void setPos(int xpos, int ypos)
	{
		x = xpos;
		y = ypos;
	}

	int getX() { return x; }
	int getY() { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
};