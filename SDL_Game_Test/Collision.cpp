#include "Collision.h"
#include "Entity&COmponent/Collider.h"
bool Collision::isCollide(const SDL_Rect& rectA, const SDL_Rect& rectB, char& direction)
{
	if (SDL_HasIntersection(&rectA, &rectB))
	{
		SDL_Point upper = { rectA.x + rectA.w / 2, rectA.y };
		SDL_Point lower = { rectA.x + rectA.w / 2, rectA.y + rectA.h };
		SDL_Point left = { rectA.x, rectA.y + rectA.h / 2 };
		SDL_Point right = { rectA.x + rectA.w, rectA.y + rectA.h / 2 };

		if (SDL_PointInRect(&upper, &rectB)) { direction = 'u'; }
		if (SDL_PointInRect(&lower, &rectB)) { direction = 'd'; }
		if (SDL_PointInRect(&left, &rectB)) { direction = 'l'; }
		if (SDL_PointInRect(&right, &rectB)) { direction = 'r'; }
		return true;
	}
	return false;
}


bool Collision::isCollide(const Collider& colA, const Collider& colB, char& direction)
{
	if (isCollide(colA.collide, colB.collide, direction))
	{
		cout << colA.tag << "hit: " << colB.tag << endl;
		return true;
	}
	return false;
}