#include "Map.h"
#include "TextureManage.h"
#include "Game.h"
#include "Entity&Component/Entity&Component.h"
#include "Entity&Component/Components.h"
#include <fstream>

extern Manager manager;

Map::Map(string id, int mapScale, int tileSize) : textureId(id), mapScale(mapScale), tileSize(tileSize)
{
	scaleSize = tileSize * mapScale;
}

Map::~Map() 
{
}

void Map::mapLoad(string path, int sizeX, int sizeY)
{
	char layer;
	char tile, tile1;
	fstream mapFile;
	mapFile.open(path);

	mapFile.get(layer);
	mapFile.ignore();
	int count = atoi(&layer);
	while (count > 0)
	{
		int srcX, srcY;
		for (int y = 0; y < sizeY; y++)
		{
			for (int x = 0; x < sizeX; x++)
			{
				mapFile.get(tile);
				mapFile.get(tile1);
				srcY = (atoi(&tile) * 10 + atoi(&tile1)) * tileSize;
				mapFile.get(tile);
				srcX = atoi(&tile) * tileSize;
				addTile(srcX, srcY, x * tileSize * mapScale, y * tileSize * mapScale);
				mapFile.ignore();
			}
			mapFile.ignore();
		}
		mapFile.ignore();
		count--;
	}

	mapFile.close();
}

void Map::interactiveMapLoad(string path, int sizeX, int sizeY, int layer)
{
	char tile;
	fstream mapFile;
	mapFile.open(path);
	int count = 1;
	while (count < layer)
	{
		for (int y = 0; y < sizeY; y++)
		{
			for (int x = 0; x < sizeX; x++)
			{
				mapFile.get(tile);
				mapFile.ignore();
			}
			mapFile.ignore();
		}
		mapFile.ignore();
		count++;
	}

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			if (tile == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<Collider>("terrain", x * scaleSize, y * scaleSize, scaleSize);
				tcol.addGroup(Game::groupColliders);
			}
			if (tile == '2')
			{
				auto& tactive(manager.addEntity());
				tactive.addComponent<Activater>("terrain", x * scaleSize, y * scaleSize, scaleSize);
				tactive.addGroup(Game::groupActivate);
			}
			mapFile.ignore();
		}
		mapFile.ignore();
	}
	mapFile.close();
}

void Map::interactiveMapUnload(vector<Entity*> colliders, vector<Entity*> activaters)
{
	for (auto& a : activaters)
	{
		a->destroy();
	}
	for (auto& c : colliders)
	{
		c->destroy();
	}
}

void Map::addTile(int srcX, int srcY, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, x, y, tileSize, mapScale, textureId);
	tile.addGroup(Game::groupMap);
}

