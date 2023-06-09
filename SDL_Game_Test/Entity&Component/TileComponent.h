#pragma once
#include "Entity&Component.h"
#include "SDL.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcR, destR;
	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int x, int y, const char* path)
	{
		texture = TextureManage::LoadTexture(path);

		srcR.x = srcX;
		srcR.y = srcY;
		srcR.w = srcR.h = 32;

		destR.x = x;
		destR.y = y;
		destR.w = destR.h = 64;
	}

	void draw() override
	{
		TextureManage::Draw(texture, srcR, destR, SDL_FLIP_NONE);
	}
};
