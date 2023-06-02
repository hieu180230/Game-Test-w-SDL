#pragma once
#include "Entity&Component.h"

class PositionComponent : public Component
{
private:
	int x, y;
public:
	int getX() { return x; }
	int getY() { return y; }

	void init() override
	{
		x = 0;
		y = 0;
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


};