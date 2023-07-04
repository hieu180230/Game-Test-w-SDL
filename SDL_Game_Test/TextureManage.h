#pragma once
#include <map>
#include "Game.h"

class TextureManage
{
private:

public:
	static SDL_Texture* LoadTexture(const char* name);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};