#include "Collision.h"
#include "Entity&COmponent/Collider.h"
bool Collision::isCollide(const SDL_Rect& rectA, const SDL_Rect& rectB, string& direction)
{
	if (SDL_HasIntersection(&rectA, &rectB))
	{
		SDL_Point upper = { rectA.x + rectA.w / 2, rectA.y };
		SDL_Point lower = { rectA.x + rectA.w / 2, rectA.y + rectA.h };
		SDL_Point left = { rectA.x, rectA.y + rectA.h / 2 };
		SDL_Point right = { rectA.x + rectA.w, rectA.y + rectA.h / 2 };

		if (SDL_PointInRect(&upper, &rectB)) { direction = "u"; }
		if (SDL_PointInRect(&lower, &rectB)) { direction = "d"; }
		if (SDL_PointInRect(&left, &rectB)) { direction = "l"; }
		if (SDL_PointInRect(&right, &rectB)) { direction = "r"; }

		if (SDL_PointInRect(&upper, &rectB) && SDL_PointInRect(&left, &rectB)) { direction = "ul"; }
		if (SDL_PointInRect(&upper, &rectB) && SDL_PointInRect(&right, &rectB)) { direction = "ur"; }
		if (SDL_PointInRect(&lower, &rectB) && SDL_PointInRect(&left, &rectB)) { direction = "dl"; }
		if (SDL_PointInRect(&lower, &rectB) && SDL_PointInRect(&right, &rectB)) { direction = "dr"; }

		return true;
	}
	return false;
}

bool Collision::isCollide(const SDL_Rect& rectA, const SDL_Rect& rectB, const SDL_Rect& rectC, string& direction)
{
	if (SDL_HasIntersection(&rectA, &rectB))
	{
		SDL_Point upper = { rectA.x + rectA.w / 2, rectA.y };
		SDL_Point lower = { rectA.x + rectA.w / 2, rectA.y + rectA.h };
		SDL_Point left = { rectA.x, rectA.y + rectA.h / 2 };
		SDL_Point right = { rectA.x + rectA.w, rectA.y + rectA.h / 2 };

		if (SDL_PointInRect(&upper, &rectB) && SDL_PointInRect(&left, &rectB)) { direction = "ul"; }
		if (SDL_PointInRect(&upper, &rectB) && SDL_PointInRect(&right, &rectB)) { direction = "ur"; }
		if (SDL_PointInRect(&lower, &rectB) && SDL_PointInRect(&left, &rectB)) { direction = "dl"; }
		if (SDL_PointInRect(&lower, &rectB) && SDL_PointInRect(&right, &rectB)) { direction = "dr"; }

		return true;
	}
	return false;
}

bool Collision::isCollide(const Collider& colA, const Collider& colB, string& direction)
{
	if (isCollide(colA.collide, colB.collide, direction))
	{
		cout << colA.tag << "hit: " << colB.tag << endl;
		return true;
	}
	return false;
}