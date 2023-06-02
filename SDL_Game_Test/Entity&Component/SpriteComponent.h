#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcR, destR;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	void setTexture(const char* path)
	{
		texture = TextureManage::LoadTexture(path);
	}

	void init() override
	{
		position = &entity->getComponent<PositionComponent>();
		
		srcR.x = srcR.y = 0;
		srcR.w = srcR.y = 32;
		destR.w = destR.h = 64;
	}

	void update() override
	{
		destR.x = position->getX();
		destR.y = position->getY();
	}

	void draw() override
	{
		TextureManage::Draw(texture, srcR, destR);
	}

};