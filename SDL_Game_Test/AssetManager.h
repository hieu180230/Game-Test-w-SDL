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
	map<string, TTF_Font*> fonts;

public:
	AssetManager(Manager* man);
	~AssetManager();

	//game objects
	void  createObject(Vector2D pos, Vector2D vel, int range, int speed, string id);

	//texture management
	void addTexture(string id, const char* path);
	SDL_Texture* getTexture(string id);

	void addFont(string id, string path, int fontsSize);
	TTF_Font* getFont(string id);
};