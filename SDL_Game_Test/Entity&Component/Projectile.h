#pragma once
#include "Entity&Component.h"
#include "Components.h"
#include "../Vector2D.h"

class Projectile : public Component
{
private:
	TransformComponent* transform;

	Vector2D velocity;
	int range = 0;
	int speed = 0;
	int distance = 0;

public:
	Projectile(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel){}
	~Projectile() {};

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->scale = 4;
		transform->velocity = velocity;
	}

	void update() override
	{
		distance += speed;

		if (distance > range)
		{
			entity->destroy();
		}
		else if (transform->position.x > Game::camera.x + Game::camera.w || transform->position.x < Game::camera.x || transform->position.y > Game::camera.y + Game::camera.h || transform->position.y < Game::camera.y)
		{
			entity->destroy();
		}
	}

};