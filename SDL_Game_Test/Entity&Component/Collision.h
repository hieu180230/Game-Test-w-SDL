#pragma once
#include<string>
#include "SDL.h"
#include "Components.h"

class Collision : public Component
{
	SDL_Rect collide;
	string tag;

	TransformComponent* transform;

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		collide.x = transform->position.x;
		collide.y = transform->position.y;
		collide.w = transform->width * transform->scale;
		collide.h = transform->height * transform->scale;
	}
};