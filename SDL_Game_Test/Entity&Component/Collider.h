#pragma once
#include<string>
#include "SDL.h"
#include "Components.h"

class Collider : public Component
{
public:	
	SDL_Rect collide;
	string tag;

	TransformComponent* transform;

	Collider(string t)
	{
		tag = t;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		Game::colliders.push_back(this);
	}

	void update() override
	{
		collide.x = static_cast<int>(transform->position.x);
		collide.y = static_cast<int>(transform->position.y);
		collide.w = (transform->width * transform->scale);
		collide.h = (transform->height * transform->scale);
	}
};