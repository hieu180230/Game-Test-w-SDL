#pragma once
#include "./Entity&Component.h"
#include "../AssetManager.h"
#include "../TextureManage.h"
#include "../Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component
{
private:
	SDL_Rect position;
	string labelText;
	string labelFont;
	SDL_Color textColor;
	SDL_Texture* textHolder;

public:
	UILabel(int xpos, int ypos, string text, string font, SDL_Color& color) : 
		labelText(text), labelFont(font), textColor(color)
	{
		position.x = xpos;
		position.y = ypos;
		setLabelText(labelText, labelFont);
	}

	~UILabel(){}

	void setLabelText(string text, string font)
	{
		SDL_Surface* surface = TTF_RenderText_Blended(Game::assets->getFont(font), text.c_str(), textColor);
		textHolder = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);

		SDL_QueryTexture(textHolder, NULL, NULL, &position.w, &position.h);

	}

	void draw() override
	{
		SDL_RenderCopy(Game::renderer, textHolder, NULL, &position);
	}
};