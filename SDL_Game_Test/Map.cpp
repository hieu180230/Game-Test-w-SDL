#include "Map.h"
#include "TextureManage.h"
#include "Game.h"
#include <fstream>

Map::Map() 
{
};

Map::~Map() 
{
};

void Map::mapLoad(string path, int sizeX, int sizeY)
{
	char tile;
	fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			srcY = atoi(&tile) * 32;
			mapFile.get(tile);
			srcX = atoi(&tile) * 32;
			Game::addTile(srcX, srcY, x * 64, y * 64);
			mapFile.ignore();
		}
	}

	mapFile.close();
};

