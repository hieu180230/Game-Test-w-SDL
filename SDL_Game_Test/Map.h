#pragma once
#include "Game.h"

class Map
{
private:
	SDL_Rect src, dst;
	SDL_Texture* dirt, * grass, * water;
	
	int map[24][32];
public:
	Map();
	~Map();

	void mapLoad(int a[24][32]);
	void drawMap();


};