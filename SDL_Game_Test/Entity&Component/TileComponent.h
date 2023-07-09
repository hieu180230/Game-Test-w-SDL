#pragma once
#include "../AssetManager.h"
#include "Entity&Component.h"
#include "../Game.h"
#include "../TextureManage.h"
#include "SDL.h"
using namespace std;
#include <iostream>

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcR, destR;
	Vector2D position;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int x, int y, int tileSize, int tileScale)
	{
		map<string, SDL_Texture*> textures = Game::assets->getTextureMap();
		position.x = x;
		position.y = y;
		int tileId = (srcX / tileSize) + (srcY / tileSize * 10);
		for (auto i : textures)
		{
			if (stoi(i.first) <= tileId && tileId <= Game::assets->getTextureLastId(stoi(i.first)))
			{
				texture = i.second;
				tileId = tileId - stoi(i.first);
				srcX = tileId % 10 * tileSize;
				srcY = tileId / 10 * tileSize;
				break;
			}
		}
		srcR.x = srcX;
		srcR.y = srcY;
		srcR.w = srcR.h = tileSize;

		destR.x = x;
		destR.y = y;
		destR.w = destR.h = tileSize * tileScale;
	}

	void update() override
	{
		destR.x = position.x - Game::camera.x;
		destR.y = position.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManage::Draw(texture, srcR, destR, SDL_FLIP_NONE);
	}
};
