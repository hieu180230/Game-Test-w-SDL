#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManage.h"
#include "Animation.h"
#include "../AssetManager.h"
#include <map>


class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcR, destR;

	bool object = false;

	bool animated = false;
	int frames = 0;
	int speed = 100;
public:

	int aniIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(string id)
	{
		setTexture(id);
	}

	SpriteComponent(string id, bool isAnimated, bool isObject)
	{
		animated = isAnimated;
		object = isObject;
		
		if (!object)
		{
			Animation idle = Animation(1, 8, 50);
			animations.emplace("Idle", idle);

			Animation walk = Animation(0, 11, 100);
			animations.emplace("Walk", walk);

			play("Idle");
		}
		else
		{
			Animation turn_on = Animation(0, 4, 200);
			animations.emplace("Turn_on", turn_on);

			Animation turn_off = Animation(1, 4, 200);
			animations.emplace("Turn_off", turn_off);
		}
		setTexture(id);
	}

	~SpriteComponent()
	{

	}

	void setTexture(string id)
	{
		texture = Game::assets->getTexture(id);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		
		srcR.w = transform->width;
		srcR.h = transform->height;
		srcR.x = 0;
		srcR.y = 0;

	}

	void update() override
	{
		if (animated) 
		{
			srcR.x = srcR.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		srcR.y = transform->height * aniIndex;
		if (!object)
		{
			destR.x = static_cast<int>(transform->position.x) - Game::camera.x;
			destR.y = static_cast<int>(transform->position.y) - Game::camera.y;
		}
		else
		{
			destR.x = static_cast<int>(transform->position.x);
			destR.y = static_cast<int>(transform->position.y);
		}
		destR.w = transform->width * transform->scale;
		destR.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManage::Draw(texture, srcR, destR, spriteFlip);
	}

	void play(const char* aniName)
	{
		frames = animations[aniName].frames;
		aniIndex = animations[aniName].index;
		speed = animations[aniName].speed;
	}
};
