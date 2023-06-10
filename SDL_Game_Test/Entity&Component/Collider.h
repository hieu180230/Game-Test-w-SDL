#pragma once
#include<string>
#include "SDL.h"
#include "Components.h"
#include "TextureManage.h"
class Collider : public Component
{
public:	
	SDL_Rect collide;
	string tag;

	SDL_Texture* tex;
	SDL_Rect srcR, destR;

	TransformComponent* transform;

	Collider(string t)
	{
		tag = t;
	}

	Collider(string t, int xpos, int ypos, int size)
	{
		tag = t;
		collide.x = xpos;
		collide.y = ypos;
		collide.w = collide.h = size;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		tex = TextureManage::LoadTexture("resource//collide_texture.png");
		srcR = { 0,0,32,32 };
		destR = { collide.x, collide.y, collide.w, collide.h };
		
	}

	void update() override
	{
		if (tag != "terrain")
		{
			collide.x = static_cast<int>(transform->position.x);
			collide.y = static_cast<int>(transform->position.y);
			collide.w = (transform->width * transform->scale);
			collide.h = (transform->height * transform->scale);
		}

		destR.x = collide.x - Game::camera.x;
		destR.y = collide.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManage::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}
};