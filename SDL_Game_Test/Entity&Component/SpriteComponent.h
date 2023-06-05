#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManage.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcR, destR;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* path)
	{
		texture = TextureManage::LoadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		
		srcR.x = srcR.y = 0;
		srcR.w = transform->width;
		srcR.h = transform->height;

	}

	void update() override
	{
		destR.x = (int)transform->position.x;
		destR.y = (int)transform->position.y;
		destR.w = transform->width * transform->scale;
		destR.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManage::Draw(texture, srcR, destR);
	}

};