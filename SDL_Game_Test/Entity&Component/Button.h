#pragma once
#include "Components.h"
#include "../TextureManage.h"

class Button : public Component
{
private:
	SDL_Rect position;
	SDL_Texture* texture;

public:
	Button() {}
	Button(int posx, int posy)
	{
		position.x = posx;
		position.y = posy;
	}
	void loadTexture(const char* path)
	{
		texture = TextureManage::LoadTexture(path);
	}
void draw() override
	{
		SDL_RenderCopy(Game::renderer, texture, NULL, &position);
	}
};