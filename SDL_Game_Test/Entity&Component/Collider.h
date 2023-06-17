#pragma once
#include<string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManage.h"

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
		destR = { collide.x, collide.y, collide.w, collide.h };//create a rectangle to store the texture and scale it
		
	}

	void update() override
	{
		//if the tag of an object is not "terrain" then make it unpassable
		if (tag != "terrain")
		{
			collide.x = static_cast<int>(transform->position.x);
			collide.y = static_cast<int>(transform->position.y);
			collide.w = (transform->width * transform->scale);
			collide.h = (transform->height * transform->scale);
		}
		//move the texture as the camera moves
		destR.x = collide.x - Game::camera.x;
		destR.y = collide.y - Game::camera.y;
	}

	//draw the texture to screen
	void draw() override
	{
		TextureManage::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}
};