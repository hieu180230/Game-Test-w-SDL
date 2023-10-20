#include "Map.h"
#include "TextureManage.h"
#include "Game.h"
#include "Entity&Component/Entity&Component.h"
#include "Entity&Component/Components.h"
#include <fstream>

extern Manager manager;

Map::Map(AssetManager* a, int mapScale, int tileSize, string mapState) : assets(a), mapScale(mapScale), tileSize(tileSize), state(mapState)
{
	scaleSize = tileSize * mapScale;
}

Map::~Map() 
{
}

void Map::mapLoad(string path, int sizeX, int sizeY)
{
	TiXmlDocument doc;
	doc.LoadFile(path);
	TiXmlElement* root = doc.RootElement();
	TiXmlElement* layers = NULL;
	int layerCount = stoi(root->Attribute("nextlayerid")) - 1;

	for (TiXmlElement* i = root->FirstChildElement(); i != NULL; i = i->NextSiblingElement())
	{
		if (i->Value() == string("tileset"))
		{
			assets->addTexture(i->Attribute("firstgid"), i->FirstChildElement()->Attribute("source"), true);
			int lastgid = stoi(i->Attribute("tilecount")) + stoi(i->Attribute("firstgid")) - 1;
			assets->addTextureId(stoi(i->Attribute("firstgid")), lastgid);
		}
		else
		{
			layers = i;
			break;
		}
	}
	while (layerCount > 0)
	{
		string matrix(layers->FirstChildElement()->GetText()), tileId;
		istringstream iss(matrix);
		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				getline(iss, tileId, ',');
				if (tileId.length() > 1 && tileId[0] == ' ')  tileId.erase(tileId.begin());
				if (tileId == "0" || tileId==" 0") tileId = "79";
				int srcX = stoi(tileId) % 10 * tileSize;
				int srcY = stoi(tileId) / 10 * tileSize;
				addTile(srcX, srcY, j * tileSize * mapScale, i * tileSize * mapScale);
			}
		}
		layers = layers->NextSiblingElement();
		cout << "next" << endl;
		layerCount--;
	}

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
				tactive.addGroup(Game::groupActivateDown);
			}
			if (tile == '5')
			{
				auto& tactive(manager.addEntity());
				tactive.addComponent<Activater>("terrain", x * scaleSize, y * scaleSize, scaleSize);
				tactive.addGroup(Game::groupActivateCheck);
			}
			if (tile == '8')
			{
				auto& tactive(manager.addEntity());
				tactive.addComponent<Activater>("terrain", x * scaleSize, y * scaleSize, scaleSize);
				tactive.addGroup(Game::groupActivateUp);
			}
			mapFile.ignore();
		}
		mapFile.ignore();
	}
	mapFile.close();
}

void Map::interactiveMapUnload(vector<Entity*> colliders, vector<Entity*> activatersUp, vector<Entity*> activatersDown, vector<Entity*> activatersCheck)
{
	for (auto& a : activatersUp)
	{
		a->destroy();
	}
	for (auto& a : activatersDown)
	{
		a->destroy();
	}
	for (auto& a : activatersCheck)
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
	tile.addComponent<TileComponent>(srcX, srcY, x, y, tileSize, mapScale);
	if (state == "above") tile.addGroup(Game::groupMapAbove);
	if (state == "below") tile.addGroup(Game::groupMapBelow);
}

