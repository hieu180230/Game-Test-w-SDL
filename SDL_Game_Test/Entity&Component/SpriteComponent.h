#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManage.h"
#include "Animation.h"
#include <map>


class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcR, destR;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int aniIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 4, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		play("Idle");
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

		if (animated)
		{
			srcR.x = srcR.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcR.y = aniIndex * transform->height;

		destR.x = static_cast<int>(transform->position.x);
		destR.y = static_cast<int>(transform->position.y);
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