#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{

public:
	Vector2D position;
	Vector2D velocity;

	int speed = 4;

	float height = 168;
	float width = 269;
	float scale = 1.0;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(float sc)
	{
		//position.Zero();
		position.x = 640;
		position.y = 200;
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

	TransformComponent(float xpos, float ypos, float h, float w, float sc)
	{
		position.x = xpos;
		position.y = ypos;
		width = w;
		height = h;
		scale = sc;
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	/*oid collider_init(int collide_x, int collide_y, int collide_w, int collide_h)
	{
		collider.x = collide_x + position.x;
		collider.y = collide_y + position.y;
		collider.w = collide_w * scale;
		collider.h = collide_h * scale;
	}*/
};