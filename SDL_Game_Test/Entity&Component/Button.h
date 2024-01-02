#pragma once
#include "Components.h"
#include "../TextureManage.h"

class Button : public Component
{
private:
	SDL_Rect srcR, desR;
	SDL_Texture* texture;
	TransformComponent* transform;
	int _index = 0;

public:
	Button() = default;
	Button(string id, int index) 
	{
		loadTexture(id);
		_index = index;
	}


	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		srcR.w = transform->width;
		srcR.h = transform->height;
		srcR.x = 0;
		srcR.y = srcR.h * _index;
		
	}
	void loadTexture(string id)
	{
		texture = Game::assets->getTexture(id);
	}
	void clicked(bool click)
	{
		if (click)
		{
			srcR.x = transform->width;
			srcR.y = srcR.h * _index;
		}
		else
		{
			srcR.x = 0;
			srcR.y = srcR.h * _index;
		}
	}
	void update() override
	{
		desR.x = (transform->position.x);
		desR.y = (transform->position.y);
		desR.w = transform->width * transform->scale;
		desR.h = transform->height * transform->scale;

	}
	void draw() override
	{
		TextureManage::Draw(texture, srcR, desR, SDL_FLIP_NONE);
	}
	SDL_Rect* getRect()
	{
		return &desR;
	}
};

class Slider : public Component
{
private:
	SDL_Rect srcR, desR;
	SDL_Texture* texture;
	TransformComponent* transform;
	int _curframe = 0;
	int _frames = 0;

public:
	Slider() = default;
	Slider(string id, int frames)
	{
		_frames = frames;
		loadTexture(id);
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		srcR.w = transform->width;
		srcR.h = transform->height;
		srcR.x = 0;
		srcR.y = 0;
	}
	void loadTexture(string id)
	{
		texture = Game::assets->getTexture(id);
	}

	void updateStatus(int s)
	{
		while (s == 1 && _curframe != _frames - 1)
		{
			_curframe++;
			srcR.x = srcR.w * _curframe;
		}
		while (s == 0 && _curframe != 0)
		{
			_curframe--;
			srcR.x = srcR.w * _curframe;
		}
	}
	void update() override
	{
		desR.x = (transform->position.x);
		desR.y = (transform->position.y);
		desR.w = transform->width * transform->scale;
		desR.h = transform->height * transform->scale;
	}
	void draw() override
	{
		TextureManage::Draw(texture, srcR, desR, SDL_FLIP_NONE);
	}
	SDL_Rect* getRect()
	{
		return &desR;
	}
};