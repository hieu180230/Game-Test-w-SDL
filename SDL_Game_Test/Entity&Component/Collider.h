#pragma once
#include<string>
#include "SDL.h"
#include "../TextureManage.h"
#include "Components.h"

/*Collider is a subclass of component class
- collide variable is to store the size of the colliding texture
- tag variable is to manage the type of a texture
- tex variable is to store texture from a file
- srcR and destR are to store the size of the source texture size and destination texture size and to scalling
- */


class Collider : public Component
{
public:	
	SDL_Rect collide;
	string tag;

	SDL_Texture* tex;
	SDL_Rect srcR, destR;

	TransformComponent* transform;

	//assign a tag to an object
	Collider(string t)
	{
		tag = t;
	}

	//assign a tag, position (x, y) and size in pixel to an object
	Collider(string t, int xpos, int ypos, int w, int h)
	{
		tag = t;
		collide.x = xpos;
		collide.y = ypos;
		collide.w = w;
		collide.h = h;
	}

	Collider(string t, int xpos, int ypos, int size)
	{
		tag = t;
		collide.x = xpos;
		collide.y = ypos;
		collide.w = collide.h = size;
	}

	//initiate the Collider class
	void init() override
	{
		//check if we already have a component to make it collidable
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>(); //get the desire component to make it a collider
		tex = TextureManage::LoadTexture("resource//collide_texture.png");//load the texture
		srcR = { 0,0,32,32 };//get full texture of the png file
		collide.x = collide.x + transform->position.x;
		collide.y = collide.y + transform->position.y;
		collide.w = collide.w * transform->scale;
		collide.h = collide.h * transform->scale;
		destR = { collide.x, collide.y, collide.w, collide.h };//create a rectangle to store the texture and scale it
		
	}

	void update() override
	{
		if (tag != "terrain")
		{
			collide.x = collide.x + transform->velocity.x * transform->speed;
			collide.y = collide.y + transform->velocity.y * transform->speed;
			destR = { collide.x, collide.y, collide.w, collide.h };
		}
		//move the texture as the camera moves
		destR.x = collide.x - Game::camera.x;
		destR.y = collide.y - Game::camera.y;
	}

	//draw the texture to screen
	void draw() override
	{
		//TextureManage::Draw(tex, srcR, destR, SDL_FLIP_NONE);
		SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(Game::renderer, &destR);
	}
};