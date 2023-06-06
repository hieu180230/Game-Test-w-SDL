#include "Collision.h"
#include "Entity&COmponent/Collider.h"
bool Collision::isCollide(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	if (SDL_HasIntersection(&rectA, &rectB))
	{
		return true;
	}
	return false;
}

bool Collision::isCollide(const Collider& colA, const Collider& colB)
{
	if (isCollide(colA.collide, colB.collide))
	{
		cout << colA.tag << "hit: " << colB.tag << endl;
		return true;
	}
	return false;
}