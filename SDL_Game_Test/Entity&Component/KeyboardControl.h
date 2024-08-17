#pragma once
#include "../Collision.h"
#include "Collider.h"
#include "Components.h"

class Collider;

class Control : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	Collider* collider;

	void init() override
	{
		sprite = &entity->getComponent<SpriteComponent>();
		transform = &entity->getComponent<TransformComponent>();
		collider = &entity->getComponent<Collider>();
	}


	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP: case SDLK_w:
			{
				transform->velocity.y = -1;
				sprite->play("Walk");
				break;
			}
			case SDLK_DOWN: case SDLK_s:
			{
				transform->velocity.y = 1;
				sprite->play("Walk");
				break;
			}
			case SDLK_RIGHT: case SDLK_d:
			{
				transform->velocity.x = 1;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			}
			case SDLK_LEFT:  case SDLK_a:
			{

				transform->velocity.x = -1;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			}
			}
		}
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP: case SDLK_w:
			{
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;
			}
			case SDLK_DOWN: case SDLK_s:
			{
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;
			}
			case SDLK_RIGHT: case SDLK_d:
			{
				transform->velocity.x = 0;
				sprite->play("Idle");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			}
			case SDLK_LEFT: case SDLK_a:
			{
				transform->velocity.x = 0;
				sprite->play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			}
			case SDLK_ESCAPE:
			{
				Game::isRunning = false;
				break;
			}
			}
		}

	}
};