#include "Collision.h"
#include "Entity&COmponent/Collider.h"
bool Collision::isCollide(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	return (rectA.x < rectB.x + rectB.w &&
		rectA.x + rectA.w > rectB.x &&
		rectA.y < rectB.y + rectB.h &&
		rectA.y + rectA.h > rectB.y);
}


bool Collision::isCollide(Collider& colA, const Collider& colB)
{
	if (isCollide(colA.collide, colB.collide))
	{
		cout << colA.tag << "hit: " << colB.tag << endl;
		return true;
	}
	return false;
}

