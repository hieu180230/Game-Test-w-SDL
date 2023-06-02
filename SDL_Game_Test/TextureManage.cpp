#include "TextureManage.h"

SDL_Texture* TextureManage::LoadTexture(const char* name)
{
	SDL_Surface* surface = IMG_Load(name);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}