#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{

public:
	Vector2D position;
	Vector2D velocity;
	int speed = 4;

	int height = 32;
	int width = 32;
	int scale = 1;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.Zero();
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}

	TransformComponent(float xpos, float ypos)
	{
		position.x = xpos;
		position.y = ypos;
	}

	TransformComponent(float xpos, float ypos, int h, int w, int sc)
	{
		position.x = xpos;
		position.y = ypos;
		height = h;
		width = w;
		scale = sc;
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
		if (position.x > 640) position.x = 0;
		if (position.x < 0)	position.x = 640;
		if (position.y > 480) position.y = 0;
		if (position.y < 0) position.y = 480;
	}
};