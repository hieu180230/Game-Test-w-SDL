#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "./glad/glad.h"
#include <iostream>
#include <vector>
#include "Game.h"

class Menu
{
private:
	SDL_Window* window;
	int choice = 1;
	SDL_Event event;
public:
	Menu();
	~Menu();

	void init(const char* title, int xpos, int ypos, int width, int height);
	void handleEvent();
	void update();
	void render();

};