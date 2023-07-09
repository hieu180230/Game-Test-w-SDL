#pragma once

#include <map>
#include <string>
#include "TextureManage.h"
#include "Vector2D.h"
#include "Game.h"
#include "Entity&Component/Entity&Component.h"
#include "SDL_ttf.h"

class AssetManager
{
private:
	Manager* manager;
	map<string, SDL_Texture*> textures;
	map<int, int> textureId;
	map<string, SDL_Texture*> mapTextures;
	map<string, TTF_Font*> fonts;

public:
	AssetManager(Manager* man);
	~AssetManager();
	//get map
	map<string, SDL_Texture*> getTextureMap();
	//game objects
	void  createObject(Vector2D pos, Vector2D vel, int range, int speed, string id);

	//texture management
	void addTexture(string id, const char* path, bool isMap);
	void addTextureId(int fid, int lid);
	SDL_Texture* getTexture(string id);
	int getTextureLastId(int fid);

	void addFont(string id, string path, int fontsSize);
	TTF_Font* getFont(string id);
};