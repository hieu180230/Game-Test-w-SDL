#pragma once
#include "Game.h"
#include <string>
#include "Entity&Component/Entity&Component.h"
#include "tinyxml.h"

class Map
{
private:
	int mapScale;
	int tileSize;
	int scaleSize;
	AssetManager* assets;
	string state;
public:
	Map(AssetManager* a, int mapScale, int tileSize, string mapState);
	~Map();

	void mapLoad(string path, int sizeX, int sizeY);
	void addTile(int srcX, int srcY, int x, int y);

};