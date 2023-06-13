#pragma once
#include "Game.h"
#include <string>
class Map
{
private:
	string textureId;
	int mapScale;
	int tileSize;
	int scaleSize;
public:
	Map(string id, int mapScale, int tileSize);
	~Map();

	void mapLoad(string path, int sizeX, int sizeY);

	void addTile(int srcX, int srcY, int x, int y);

};