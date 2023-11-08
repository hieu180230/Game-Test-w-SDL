#pragma once
#include "Components.h"
#include "../TextureManage.h"

class Button : public Component
{
private:
	SDL_Rect srcR, desR;
	SDL_Texture* texture;
	TransformComponent* transform;

	bool animated = false;
	int frames = 0;

public:
	int aniIndex = 0;
	Button() = default;
	Button(string id) 
	{
		loadTexture(id);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		srcR.x = srcR.y = 0;
		srcR.w = transform->width;
		srcR.h = transform->height;
	}
	void loadTexture(string id)
	{
		texture = Game::assets->getTexture(id);
	}
	void update() override
	{

		if (animated)
		{
			srcR.x = srcR.w * static_cast<int>((SDL_GetTicks() / 100) % frames);
		}

		srcR.y = aniIndex * transform->height;

		desR.x = static_cast<int>(transform->position.x) - Game::camera.x;
		desR.y = static_cast<int>(transform->position.y) - Game::camera.y;
		desR.w = transform->width * transform->scale;
		desR.h = transform->height * transform->scale;
	}
	void draw() override
	{
		TextureManage::Draw(texture, srcR, desR, SDL_FLIP_NONE);
	}
};