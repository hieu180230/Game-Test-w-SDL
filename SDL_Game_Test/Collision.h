#pragma once
#include <SDL.h>
#include <string>
#include <tuple>
#include "Entity&Component/Entity&Component.h"
using namespace std;
class Collider;

class Collision
{
public:
	static bool isCollide(const SDL_Rect& rectA, const SDL_Rect& rectB, SDL_Rect& res);
	static bool isCollide(Collider& colA, const Collider& colB);
	static void collisionResolve(Entity& player, vector<Entity*> colliders);
};
