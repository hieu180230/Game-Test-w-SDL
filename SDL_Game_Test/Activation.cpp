#include "Entity&COmponent/Activater.h"
#include "Activation.h"
#include "Collision.h"
#include <math.h>

bool Activation::activationResolve(Entity& player, vector<Entity*> activatersUp, vector<Entity*> activatersDown, vector<Entity*> activatersCheck, int& z)
{
	SDL_Rect res;
	SDL_Rect playerCollider = player.getComponent<Collider>().collide;
	for (auto& a : activatersCheck)
	{
		SDL_Rect activater = a->getComponent<Activater>().collide;
		if (Collision::isCollide(playerCollider, activater, res))
		{
			for (auto& aUp : activatersUp)
			{
				SDL_Rect upCollider = aUp->getComponent<Activater>().collide;
				if (Collision::isCollide(playerCollider, upCollider, res))
				{
					z++;
					return true;
				}
			}
			for (auto& aDown : activatersDown)
			{
				SDL_Rect downCollider = aDown->getComponent<Activater>().collide;
				if (Collision::isCollide(playerCollider, downCollider, res))
				{
					z--;
					return true;
				}
			}
			return false;
		}
	}
	return false;
}