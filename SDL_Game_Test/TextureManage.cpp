#include "TextureManage.h"

SDL_Texture* TextureManage::LoadTexture(const char* name)
{
	SDL_Surface* surface = IMG_Load(name);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void TextureManage::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}