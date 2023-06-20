#pragma once
#include <SDL.h>
#include <string>
using namespace std;
class Collider;

class Collision
{
public:
	static bool isCollide(const SDL_Rect& rectA, const SDL_Rect& rectB, string& direction);
	static bool isCollide(const SDL_Rect& rectA, const SDL_Rect& rectB, const SDL_Rect& rectC, string& direction);
	static bool isCollide(const Collider& colA, const Collider& colB, string& direction);
};