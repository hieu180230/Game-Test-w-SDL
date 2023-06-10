#pragma once
#include "Entity&Component.h"
#include "SDL.h"

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

	TileComponent(int srcX, int srcY, int x, int y, int tileSize, int tileScale, const char* path)
	{
		texture = TextureManage::LoadTexture(path);

		position.x = x;
		position.y = y;

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
