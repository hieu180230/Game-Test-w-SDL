#pragma once
#include "Game.h"

class Object
{
private:
	int x = 0;
	int y = 0;

	SDL_Texture* texture;
	SDL_Rect srcR, destR;

public:
	Object(const char* texture, int xpos, int ypos);
	~Object();

	void Update();
	void Render();

	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
};