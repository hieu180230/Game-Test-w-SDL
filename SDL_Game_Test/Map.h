#pragma once
#include "Game.h"
#include <string>
#include "Entity&Component/Entity&Component.h"

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
	void interactiveMapLoad(string path, int sizeX, int sizeY, int layer);
	void interactiveMapUnload(vector<Entity*> colliders, vector<Entity*> activatersUp, vector<Entity*> activatersDown, vector<Entity*> activatersCheck);

	void addTile(int srcX, int srcY, int x, int y);

};